/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */     
#include "stm32f429i_discovery.h"
#include "dht22.h"
#include "dht_tim.h"
/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId defaultTaskHandle;
osThreadId HWInitTaskHandle;
osThreadId LED3BlinkTaskHandle;
osThreadId LED4BlinkTaskHandle;
osThreadId ReadButtonTaskHandle;
osThreadId DHT22TaskHandle;

/* USER CODE BEGIN Variables */
void HWInitTask(void const * argument);
void LED3BlinkTask(void const * argument);
void LED4BlinkTask(void const * argument);
void ReadButtonTask(void const * argument);
void DHT22Task(void const * argument);

static dht22_data data;
/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartDefaultTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
	osThreadDef(HWInit, HWInitTask, osPriorityNormal, 0, 128);
	HWInitTaskHandle = osThreadCreate(osThread(HWInit), NULL);

	osThreadDef(LED3Blink, LED3BlinkTask, osPriorityAboveNormal, 0, 128);
	LED3BlinkTaskHandle = osThreadCreate(osThread(LED3Blink), NULL);

	osThreadDef(LED4Blink, LED4BlinkTask, osPriorityAboveNormal, 0, 128);
	LED4BlinkTaskHandle = osThreadCreate(osThread(LED4Blink), NULL);

	osThreadDef(ReadButton, ReadButtonTask, osPriorityAboveNormal, 0, 128);
	ReadButtonTaskHandle = osThreadCreate(osThread(ReadButton), NULL);

	osThreadDef(DHT22Sensor, DHT22Task, osPriorityHigh, 0, 128);
	DHT22TaskHandle = osThreadCreate(osThread(DHT22Sensor), NULL);
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */
	/* Infinite loop */
	for(;;)
	{
		osDelay(1);
	}
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Application */
/* StartDefaultTask function */
void HWInitTask(void const * argument)
{

	/* USER CODE BEGIN StartDefaultTask */

	/* Initialize USER Button in EXTI mode and 2 LED buttons to be "toggle-able" */
	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);
	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4);

	/* Terminate/delete thread from active threads. */
	osThreadTerminate(HWInitTaskHandle);

	/* Infinite loop */
	for(;;)
	{
		osDelay(1);
	}
	/* USER CODE END StartDefaultTask */
}

/* StartDefaultTask function */
void LED3BlinkTask(void const * argument)
{

	/* USER CODE BEGIN StartDefaultTask */

	/* Initialize USER Button in EXTI mode and 2 LED buttons to be "toggle-able" */
	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);
	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4);

	/* Infinite loop */
	for(;;)
	{
		osDelay(1);
	}
	/* USER CODE END StartDefaultTask */
}

/* StartDefaultTask function */
void LED4BlinkTask(void const * argument)
{

	/* USER CODE BEGIN StartDefaultTask */

	/* Initialize USER Button in EXTI mode and 2 LED buttons to be "toggle-able" */
	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);
	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4);

	/* Infinite loop */
	for(;;)
	{
		osDelay(1);
	}
	/* USER CODE END StartDefaultTask */
}

/* StartDefaultTask function */
void ReadButtonTask(void const * argument)
{

	/* USER CODE BEGIN StartDefaultTask */

	/* Initialize USER Button in EXTI mode and 2 LED buttons to be "toggle-able" */
	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);
	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4);

	/* Terminate/delete thread from active threads. */

	/* Infinite loop */
	for(;;)
	{
		osDelay(1);
	}
	/* USER CODE END StartDefaultTask */
}

void DHT22Task(void const * argument)
{
	DTIM_Initialize();
	DHT22_Init();

	  while (1)
	  {
	     /* Temporarily disable all interrupts to ensure accurate timing */
	    __disable_irq ();

	    if ( DHT22_Read (&data) == true )
	    {
	      data.temperature;
	      data.humidity;
	    } else {
	      /*
	        Error - check response code in data.rcv_response, for more info
	        attach debugger and examine impulse times in data.bits[40] (dht22.c)
	      */
	    }

	    __enable_irq ();

	    osDelay(4000);
	  }
}

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
