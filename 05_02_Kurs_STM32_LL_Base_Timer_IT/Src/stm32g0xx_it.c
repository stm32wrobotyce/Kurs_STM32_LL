/*
 * stm32g0xx_it.c
 *
 *  Created on: Sep 21, 2022
 *      Author: piotr
 */

#include "main.h"

void TIM2_IRQHandler(void)
{
	if(LL_TIM_IsActiveFlag_UPDATE(TIM2) == 1)
	{
		LL_TIM_ClearFlag_UPDATE(TIM2);

		LL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
	}
}
