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

void I2C1_IRQHandler(void)
{
	if(LL_I2C_IsActiveFlag_TXIS(I2C1) && LL_I2C_IsEnabledIT_TX(I2C1))
	{
		i2c_it_transmit_callback();
	}
	else if(LL_I2C_IsActiveFlag_RXNE(I2C1) && LL_I2C_IsEnabledIT_RX(I2C1))
	{
		i2c_it_receive_callback();
	}
	else if(LL_I2C_IsActiveFlag_STOP(I2C1) && LL_I2C_IsEnabledIT_STOP(I2C1))
	{
		LL_I2C_ClearFlag_STOP(I2C1);
		LL_I2C_DisableIT_STOP(I2C1);
	}
}
