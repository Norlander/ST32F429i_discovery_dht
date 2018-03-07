#ifndef TIM_H_
#define TIM_H_

#define DELAY_US_TIM		TIM10

#define DELAY_MS_TIM		TIM7

#include <stdint.h>

TIM_HandleTypeDef htim7;

void
Delay_us (uint16_t nTime);
void
Delay_ms (uint16_t nTime);

void
DTIM_Initialize ();

#endif

