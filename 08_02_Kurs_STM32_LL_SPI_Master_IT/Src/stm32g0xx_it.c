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

void SPI1_IRQHandler(void)
{
	if(LL_SPI_IsActiveFlag_TXE(SPI1) && LL_SPI_IsEnabledIT_TXE(SPI1))
	{
		spi_it_transmit_callback();
	}

	if(LL_SPI_IsActiveFlag_RXNE(SPI1) && LL_SPI_IsEnabledIT_RXNE(SPI1))
	{
		spi_it_receive_callback();
	}
}
