#include "headers/stm32h7a3xxq.h"
#include "headers/core_cm7.h"
#include "timers/systick/systick.h"

void init_systick(void)
{
    SysTick->CTRL |= (0b1 << 1);
    SysTick->CTRL |= (0b1 << 2);
    SysTick->LOAD = 0x1869F;
    SysTick->VAL = 0;
    SysTick->CTRL |= (0b1 << 0);
}