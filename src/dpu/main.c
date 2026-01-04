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

/* Prototype buffer size for DPU side (limited to 2048 by MRAM API) */
#define PROTO_BUFFER_SIZE 2048

/* Place a buffer in MRAM (persistent across contexts) */
__mram_noinit uint8_t mram_buffer[PROTO_BUFFER_SIZE];

int main() {
    /* Simple DPU kernel:
     * 1. Read PROTO_BUFFER_SIZE bytes from MRAM into a WRAM local buffer
     * 2. Perform a noop (or invert first byte) to simulate processing
     * 3. Write back to MRAM
     * This kernel is intentionally minimal for testing host↔DPU transfers.
     */
    uint8_t local[PROTO_BUFFER_SIZE];

    /* Read from MRAM offset 0 (signature: mram_read(__mram_ptr from, void* to, size)) */
    mram_read((__mram_ptr void*)mram_buffer, local, PROTO_BUFFER_SIZE);

    /* Simple processing: invert first byte */
    local[0] = ~local[0];

    /* Write back to MRAM (signature: mram_write(const void* from, __mram_ptr to, size)) */
    mram_write(local, (__mram_ptr void*)mram_buffer, PROTO_BUFFER_SIZE);

    return 0;
}

#else

/* Fallback for non-DPU compilation */
int main() {
    return 0;
}

#endif
