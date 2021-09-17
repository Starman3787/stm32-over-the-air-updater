#include <stdbool.h>
#include "headers/stm32h7a3xxq.h"
#include "drivers/led/led.h"

void init_led(void)
{
    RCC->AHB4ENR |= RCC_AHB4ENR_GPIOEEN;

    GPIOE->MODER &= ~(0b11 << (1 * 2));
    GPIOE->MODER |= (0b01 << (1 * 2));
}

void write_led(bool state)
{
    if (state == true)
        GPIOE->ODR |= (0b1 << 1);
    else
        GPIOE->ODR &= ~(0b1 << 1);
}

void toggle_led(void)
{
    GPIOE->ODR ^= (0b1 << 1);
}