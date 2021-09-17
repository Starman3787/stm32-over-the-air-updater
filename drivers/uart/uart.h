#ifndef DRIVERS_UART_H
#define DRIVERS_UART_H

#include <stdint.h>

extern uint8_t uart_pins[2];

#define CORE_CLOCK      (64000000U)
#define BAUD_RATE       (9600U)

int8_t init_uart(void);
void write_uart(char byte);

#endif