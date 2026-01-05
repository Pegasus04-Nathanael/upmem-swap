/**
 * UPMEM Swap - DPU Kernel
 * 
 * This kernel runs on UPMEM DPU co-processors
 * to accelerate swap operations.
 * 
 * Build: make (when UPMEM SDK is available)
 */

/* DPU includes (available with SDK) */
#ifdef __DPU__
#include <mram.h>
#include <stdint.h>

/* CRITICAL: mram_read/mram_write max size is 2048 bytes
 * Start small (256 bytes) for reliable testing */
#define PROTO_BUFFER_SIZE 256

/* Place a buffer in MRAM (persistent across contexts) */
__mram_noinit uint8_t mram_buffer[PROTO_BUFFER_SIZE];

int main() {
    /* Simple DPU kernel:
     * 1. Read PROTO_BUFFER_SIZE bytes from MRAM into a WRAM local buffer
     * 2. Invert first byte to verify DPU execution
     * 3. Write back to MRAM
     * This kernel is intentionally minimal for testing host↔DPU transfers.
     */
    uint8_t local[PROTO_BUFFER_SIZE];

    /* Read from MRAM offset 0 
     * Signature: mram_read(__mram_ptr const void *from, void *to, size_t nb_of_bytes)
     * nb_of_bytes MUST be <= 2048 and multiple of 8 for best performance */
    mram_read((__mram_ptr void const *)mram_buffer, local, PROTO_BUFFER_SIZE);

    /* Simple processing: invert first byte to prove DPU ran */
    local[0] = ~local[0];

    /* Write back to MRAM
     * Signature: mram_write(const void *from, __mram_ptr void *to, size_t nb_of_bytes) */
    mram_write(local, (__mram_ptr void *)mram_buffer, PROTO_BUFFER_SIZE);

    return 0;
}

#else

/* Fallback for non-DPU compilation */
int main() {
    return 0;
}

#endif