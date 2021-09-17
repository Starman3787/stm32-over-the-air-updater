#include <stdbool.h>
#include "timers/systick/systick.h"
#include "drivers/led/led.h"
#include "drivers/uart/uart.h"
#include "util/delay/delay.h"

volatile uint64_t ticks = 0;
volatile time_t unix = 0;

void main(void)
{    
    toggle_led();
    while (1)
    {
        write_uart('a');
        delay_ms(1000);
        toggle_led();
    }
}