#ifndef DRIVERS_LED_H_
#define DRIVERS_LED_H_

#include <stdint.h>
#include <stdbool.h>

void init_led(void);
void write_led(bool state);
void toggle_led(void);

#endif