 // main.c
#include <stdint.h>

// Register addresses (STM32F4 Discovery - GPIOD)
#define PERIPH_BASE       0x40000000
#define AHB1PERIPH_BASE   (PERIPH_BASE + 0x00020000)
#define GPIOD_BASE        (AHB1PERIPH_BASE + 0x0C00)
#define RCC_BASE          (AHB1PERIPH_BASE + 0x3800)

#define RCC_AHB1ENR       (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define GPIOD_MODER       (*(volatile uint32_t *)(GPIOD_BASE + 0x00))
#define GPIOD_ODR         (*(volatile uint32_t *)(GPIOD_BASE + 0x14))

#define LED_PIN           12

void delay(void) {
    for (volatile int i = 0; i < 100000; i++) {}
}

int main(void) {
    // Enable GPIOD clock
    RCC_AHB1ENR |= (1 << 3);

    // Set PD12 as output
    GPIOD_MODER &= ~(0x3 << (LED_PIN * 2)); // Clear mode
    GPIOD_MODER |=  (0x1 << (LED_PIN * 2)); // Set output mode

    // Toggle LED
    while (1) {
        GPIOD_ODR ^= (1 << LED_PIN);
        delay();
    }
}
