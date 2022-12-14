/*
 * stm32g0xx_it.c
 *
 *  Created on: Sep 21, 2022
 *      Author: piotr
 */

#include "main.h"

uint32_t push_diff_time_ms = 0;

void TIM2_IRQHandler(void)
{
	if(LL_TIM_IsActiveFlag_CC1(TIM2) == 1)
	{
		LL_TIM_ClearFlag_CC1(TIM2);
		push_diff_time_ms = LL_TIM_IC_GetCaptureCH1(TIM2);
		LL_TIM_SetCounter(TIM2, 0UL);
	}
}
