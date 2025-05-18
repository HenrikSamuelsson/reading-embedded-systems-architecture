// startup.c
#include <stdint.h>

extern int main(void);

// Linker symbols
extern uint32_t _sbss, _ebss, _sdata, _edata, _etext;

void Reset_Handler(void) {
    // Initialize .data
    uint32_t *src = &_etext;
    uint32_t *dst = &_sdata;
    while (dst < &_edata)
        *dst++ = *src++;

    // Zero .bss
    dst = &_sbss;
    while (dst < &_ebss)
        *dst++ = 0;

    main();
}

// Vector table (only reset handler for now)
__attribute__((section(".isr_vector")))
const void *vector_table[] = {
    (void *)(0x20000000 + 128 * 1024), // Initial stack pointer (top of RAM)
    Reset_Handler                      // Reset handler
};
