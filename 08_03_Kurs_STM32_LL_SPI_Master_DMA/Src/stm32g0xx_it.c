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

void DMA_Channel1_IRQHandler(void)
{
	if (LL_DMA_IsActiveFlag_TC1(DMA1))
	{
		LL_DMA_ClearFlag_TC1(DMA1);

		spi_dma_transmit_callback();
	}
}

void DMA_Channel2_3_IRQHandler(void)
{
	if (LL_DMA_IsActiveFlag_TC2(DMA1))
	{
		LL_DMA_ClearFlag_TC2(DMA1);

		spi_dma_receive_callback();
	}
}
