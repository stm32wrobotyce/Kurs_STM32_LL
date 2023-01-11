/*
 * stm32g0xx_it.c
 *
 *  Created on: Sep 21, 2022
 *      Author: piotr
 */

#include "main.h"

void SysTick_Handler(void)
{
	software_timer_inc_ms_tick();
}

void ADC_COMP_IRQHandler(void)
{
	if(LL_ADC_IsActiveFlag_EOC(ADC1) != 0)
	{
		adc_conversion_complete_callback();

		LL_ADC_ClearFlag_EOC(ADC1);
	}

	if(LL_ADC_IsActiveFlag_EOS(ADC1) != 0)
	{
		adc_sequence_complete_callback();

		LL_ADC_ClearFlag_EOS(ADC1);
	}
}
