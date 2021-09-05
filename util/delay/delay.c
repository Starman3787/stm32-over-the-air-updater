#include <stdint.h>
#include "timers/systick/systick.h"
#include "util/delay/delay.h"

void delay_ms(uint32_t milliseconds)
{
    uint64_t waitUntilTicks = ticks + milliseconds;
    uint64_t currentTicks = ticks;
    do
    {
        currentTicks = ticks;
    } while (currentTicks < waitUntilTicks);
}