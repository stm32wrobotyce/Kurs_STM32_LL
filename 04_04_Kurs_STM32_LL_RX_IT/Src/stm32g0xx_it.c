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

void USART2_IRQHandler(void)
{
	if(LL_USART_IsEnabledIT_RXNE(USART2) && LL_USART_IsActiveFlag_RXNE(USART2))
	{
		usart_it_rx_not_empty_callback();
	}
}
