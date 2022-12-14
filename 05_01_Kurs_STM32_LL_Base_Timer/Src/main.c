/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>

#include "main.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
	//RCC
	LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);

	LL_RCC_HSI_Enable();
	while(LL_RCC_HSI_IsReady() != 1)
		;

	LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_1, 8, LL_RCC_PLLR_DIV_2);

	LL_RCC_PLL_Enable();
	while(LL_RCC_PLL_IsReady() != 1)
		;

	LL_RCC_PLL_EnableDomain_SYS();

	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);

	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
	while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
		;

	LL_SetSystemCoreClock(64000000);
	LL_Init1msTick(64000000);

	//GPIO
	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

	LL_GPIO_SetPinOutputType(LED_GREEN_GPIO_Port, LED_GREEN_Pin, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(LED_GREEN_GPIO_Port, LED_GREEN_Pin, LL_GPIO_PULL_NO);
	LL_GPIO_SetPinSpeed(LED_GREEN_GPIO_Port, LED_GREEN_Pin, LL_GPIO_SPEED_FREQ_LOW);
	LL_GPIO_SetPinMode(LED_GREEN_GPIO_Port, LED_GREEN_Pin, LL_GPIO_MODE_OUTPUT);

	//TIMER
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);

	LL_TIM_SetClockSource(TIM2, LL_TIM_CLOCKSOURCE_INTERNAL);
	LL_TIM_SetCounterMode(TIM2, LL_TIM_COUNTERMODE_UP);

	//uint32_t timer_arr = __LL_TIM_CALC_ARR(64000000, 64000, 1);

	LL_TIM_SetPrescaler(TIM2, 64000-1);
	LL_TIM_SetAutoReload(TIM2, 1000-1);
	LL_TIM_GenerateEvent_UPDATE(TIM2);

	LL_TIM_ClearFlag_UPDATE(TIM2);
	LL_TIM_EnableCounter(TIM2);

	while (1)
	{
		if(LL_TIM_IsActiveFlag_UPDATE(TIM2) == 1)
		{
			LL_TIM_ClearFlag_UPDATE(TIM2);
			LL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
		}
	}
}
