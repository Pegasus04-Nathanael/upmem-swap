/**
 * UPMEM Swap - Host Application
 * 
 * This application orchestrates DPU co-processors to optimize
 * memory swapping operations.
 * 
 * Build: make (when UPMEM SDK is available)
 * Run: ./build/host
 */

#include "main.h"
#include <time.h>

/* Prototype buffer size for quick micro-bench: 2KB (must match DPU MRAM limits) */
#define PROTO_BUFFER_SIZE 2048

void* allocate_swap_buffer(size_t size) {
    void* buffer = malloc(size);
    if (!buffer) {
        fprintf(stderr, "ERROR: Failed to allocate swap buffer\n");
        return NULL;
    }
    return buffer;
}

void free_swap_buffer(void* buffer) {
    if (buffer) {
        free(buffer);
    }
}

static long diff_nsec(struct timespec a, struct timespec b) {
    return (b.tv_sec - a.tv_sec) * 1000000000L + (b.tv_nsec - a.tv_nsec);
}

int main(int argc, char* argv[]) {
    printf("=== UPMEM Swap Prototype ===\n");
    printf("UPMEM SDK Status: ");

#ifdef HAVE_DPU_H
    printf("AVAILABLE\n");
    printf("Note: DPU execution path not implemented yet - falling back to simulation.\n");
#else
    printf("NOT AVAILABLE\n");
    printf("Running in development mode (simulated transfer)\n");
#endif

    /* Use a small buffer for quick iteration */
    size_t buffer_size = PROTO_BUFFER_SIZE;
    void* swap_buffer = allocate_swap_buffer(buffer_size);

    if (!swap_buffer) {
        return 1;
    }

    /* Initialize test pattern */
    memset(swap_buffer, 0xA5, buffer_size);

#ifdef HAVE_DPU_H
    /* Real DPU path using UPMEM Host API */
    struct dpu_set_t dpu_set = {0};
    struct dpu_program_t *program = NULL;
    dpu_error_t err;

    /* Try to allocate one rank (NR_DPUS may be 1) */
    err = dpu_alloc_ranks(1, NULL, &dpu_set);
    if (err != DPU_OK) {
        fprintf(stderr, "DPU allocation failed: %s\n", dpu_error_to_string(err));
        fprintf(stderr, "Falling back to simulation path.\n");
        goto simulated_transfer;
    }

    /* Load program onto DPUs */
    err = dpu_load(dpu_set, "build/dpu", &program);
    if (err != DPU_OK) {
        fprintf(stderr, "DPU load failed: %s\n", dpu_error_to_string(err));
        dpu_free(dpu_set);
        goto simulated_transfer;
    }

    /* Copy host buffer into DPU MRAM symbol 'mram_buffer' */
    err = dpu_copy_to(dpu_set, "mram_buffer", 0, swap_buffer, buffer_size);
    if (err != DPU_OK) {
        fprintf(stderr, "dpu_copy_to failed: %s\n", dpu_error_to_string(err));
        dpu_free(dpu_set);
        goto simulated_transfer;
    }

    struct timespec t0_dpu, t1_dpu;
    clock_gettime(CLOCK_MONOTONIC, &t0_dpu);

    /* Launch DPUs synchronously */
    err = dpu_launch(dpu_set, DPU_SYNCHRONOUS);
    if (err != DPU_OK) {
        fprintf(stderr, "dpu_launch failed: %s\n", dpu_error_to_string(err));
        dpu_free(dpu_set);
        goto simulated_transfer;
    }

    /* Retrieve processed data back into swap_buffer */
    err = dpu_copy_from(dpu_set, "mram_buffer", 0, swap_buffer, buffer_size);
    clock_gettime(CLOCK_MONOTONIC, &t1_dpu);

    if (err != DPU_OK) {
        fprintf(stderr, "dpu_copy_from failed: %s\n", dpu_error_to_string(err));
        dpu_free(dpu_set);
        goto simulated_transfer;
    }

        long ns_dpu = diff_nsec(t0_dpu, t1_dpu);
        printf("DPU round-trip transfer: %zu bytes in %ld ns (%.3f us)\n",
            buffer_size, ns_dpu, ns_dpu / 1000.0);

    /* Verify expected transformation: first byte inverted by DPU */
    uint8_t expected = (uint8_t)~0xA5;
    printf("Verification (first byte): %s\n", swap_buffer && ((uint8_t*)swap_buffer)[0] == expected ? "OK" : "FAIL");

    dpu_free(dpu_set);
    printf("DPU prototype run complete\n");
    return 0;

simulated_transfer:
    ; /* label target */
#endif /* HAVE_DPU_H */

    /* Simulated host-only transfer path */
    void* device_buffer = malloc(buffer_size);
    if (!device_buffer) {
        fprintf(stderr, "ERROR: Failed to allocate device buffer\n");
        free_swap_buffer(swap_buffer);
        return 1;
    }

    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);
    memcpy(device_buffer, swap_buffer, buffer_size);
    memcpy(swap_buffer, device_buffer, buffer_size);
    clock_gettime(CLOCK_MONOTONIC, &t1);

    long ns_sim = diff_nsec(t0, t1);
    printf("Simulated round-trip transfer: %zu bytes in %ld ns (%.3f us)\n",
           buffer_size, ns_sim, ns_sim / 1000.0);

    /* Verify pattern (basic check) */
    uint8_t* p = (uint8_t*)swap_buffer;
    int mismatch = 0;
    for (size_t i = 0; i < buffer_size; i++) {
        if (p[i] != 0xA5) { mismatch = 1; break; }
    }
    printf("Verification: %s\n", mismatch ? "FAIL" : "OK");

    free(device_buffer);
    free_swap_buffer(swap_buffer);
    printf("Prototype run complete\n");
    return 0;
}
