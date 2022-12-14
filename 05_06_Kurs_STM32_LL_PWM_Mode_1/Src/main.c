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

#define LED_TASK_TIME	10

#define INCREMENT		0
#define DECREMENT		1

#define INC_DEC_STEP	1

uint32_t pwm_duty = 0;
uint32_t pwm_dir = INCREMENT;

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
	LL_SYSTICK_EnableIT();

	//GPIO TIM2_CH1_IC
	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

	LL_GPIO_SetPinPull(TIM2_CH1_OC_Port, TIM2_CH1_OC_Pin, LL_GPIO_PULL_NO);
	LL_GPIO_SetPinSpeed(TIM2_CH1_OC_Port, TIM2_CH1_OC_Pin, LL_GPIO_SPEED_FREQ_LOW);
	LL_GPIO_SetAFPin_0_7(TIM2_CH1_OC_Port, TIM2_CH1_OC_Pin, LL_GPIO_AF_2);
	LL_GPIO_SetPinMode(TIM2_CH1_OC_Port, TIM2_CH1_OC_Pin, LL_GPIO_MODE_ALTERNATE);

	//TIMER BASE
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);

	LL_TIM_SetClockSource(TIM2, LL_TIM_CLOCKSOURCE_INTERNAL);
	LL_TIM_SetCounterMode(TIM2, LL_TIM_COUNTERMODE_UP);

	LL_TIM_SetPrescaler(TIM2, 640-1);
	LL_TIM_SetAutoReload(TIM2, 100-1);
	LL_TIM_GenerateEvent_UPDATE(TIM2);

	LL_TIM_ClearFlag_UPDATE(TIM2);

	//TIM2_CH1
	LL_TIM_OC_SetCompareCH1(TIM2, pwm_duty);
	LL_TIM_OC_SetMode(TIM2, LL_TIM_CHANNEL_CH1, LL_TIM_OCMODE_PWM1);
	LL_TIM_OC_SetPolarity(TIM2, LL_TIM_CHANNEL_CH1, LL_TIM_OCPOLARITY_HIGH);

	LL_TIM_CC_EnableChannel(TIM2, LL_TIM_CHANNEL_CH1);
	LL_TIM_EnableCounter(TIM2);

	software_timer_t led_timer;
	software_timer_task_init(&led_timer, LED_TASK_TIME);

	while (1)
	{
		  if((software_timer_get_ms_tick() - led_timer.ms_tick) >= led_timer.task_time)
		  {
			  led_timer.ms_tick = software_timer_get_ms_tick();

			  if(pwm_dir == INCREMENT)
			  {
				  pwm_duty += INC_DEC_STEP;

				  if(pwm_duty == (LL_TIM_GetAutoReload(TIM2)+1))
				  {
					  pwm_dir = DECREMENT;
				  }
			  }
			  else if(pwm_dir == DECREMENT)
			  {
				  pwm_duty -= INC_DEC_STEP;

				  if(pwm_duty == 0)
				  {
					  pwm_dir = INCREMENT;
				  }
			  }

			  LL_TIM_OC_SetCompareCH1(TIM2, pwm_duty);
		  }
	}
}
