/*
 * dht_tim.c
 *
 *  Created on: 23 Feb 2018
 *      Author: matte
 */


#include "tim.h"

//#include <stm32f4xx_hal_tim.h>
//#include <stm32f4xx_hal_rcc.h>
#include "stm32f4xx_hal.h"
#include "stm32f429i_discovery.h"

void
Delay_us (uint16_t nTime)
{
  DELAY_US_TIM->CNT = 0;

  while (DELAY_US_TIM->CNT < nTime)
    ;
}

void
Delay_ms (uint16_t nTime)
{
  DELAY_MS_TIM->CNT = 0;
//#error "add #ifdef DEBUG, toggle LED pin to see that TIM7 is setup correctly... Read with Saleae?!"
  while (DELAY_MS_TIM->CNT < nTime)
    ;
}

void DTIM_Initialize ()
{
  //RCC_APB1PeriphClockCmd (DELAY_US_TIM_APB, ENABLE);
  /* APB1 use for ms resolution. */
  __HAL_RCC_TIM7_CLK_ENABLE();

  volatile uint32_t apb1clock = HAL_RCC_GetPCLK1Freq();
  volatile uint32_t apb2clk = HAL_RCC_GetPCLK2Freq();
  volatile uint32_t hclk = HAL_RCC_GetHCLKFreq();
  volatile uint32_t sysclk = HAL_RCC_GetSysClockFreq();

  TIM_HandleTypeDef htim7;
  htim7.Instance = TIM7;
  /* 42 MHz on APB1 timer bus */
  htim7.Init.ClockDivision = TIM_CLOCKDIVISION_DIV2;
  /* 21 MHz at this stage. Divide it down to 1000Hz by using 21 000 --> 20 999 divider */
  htim7.Init.Prescaler = 20999;
  htim7.Init.Period = 1000;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;

  HAL_TIM_Base_Init(&htim7);


  /* APB2 use for us resolution. */
  __HAL_RCC_TIM10_CLK_ENABLE();

  TIM_HandleTypeDef htim10;
  htim10.Instance = TIM10;
  /* 168 MHz on APB1 timer bus */
  htim10.Init.ClockDivision = TIM_CLOCKDIVISION_DIV4;
  /* 42 MHz at this stage. Divide it down to 1MHz by using 42 --> 41 divider */
  htim10.Init.Prescaler = 41;
  htim10.Init.Period = 0xffff;
  htim10.Init.CounterMode = TIM_COUNTERMODE_UP;

  HAL_TIM_Base_Init(&htim10);

  BSP_LED_Init(LED3);

  NVIC_SetPriority(TIM7_IRQn, 2);
  NVIC_EnableIRQ(TIM7_IRQn);
  HAL_TIM_Base_Start_IT(&htim7);
  HAL_TIM_Base_Start(&htim10);

}
