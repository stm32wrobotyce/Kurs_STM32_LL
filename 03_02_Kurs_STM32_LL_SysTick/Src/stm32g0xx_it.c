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
