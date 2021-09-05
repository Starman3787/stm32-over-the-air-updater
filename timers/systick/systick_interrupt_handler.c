#include "./systick.h"

void SysTick_Handler(void)
{
    ticks++;
    if (ticks % 1000 == 0)
        unix++;
}