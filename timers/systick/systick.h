#ifndef TIMERS_SYSTICK_H_
#define TIMERS_SYSTICK_H_

#include <stdint.h>
#include <time.h>

void SysTick_Handler(void);

void init_systick(void);

extern volatile uint64_t ticks;
extern volatile time_t unix;

#endif