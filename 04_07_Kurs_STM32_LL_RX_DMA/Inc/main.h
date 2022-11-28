/*
 * main.h
 *
 *  Created on: Sep 21, 2022
 *      Author: piotr
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_system.h"
#include "stm32g0xx_ll_cortex.h"
#include "stm32g0xx_ll_utils.h"
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_tim.h"
#include "stm32g0xx_ll_usart.h"
#include "stm32g0xx_ll_dma.h"
#include "stm32g0xx_ll_dmamux.h"

#include "software_timer.h"
#include "usart_comm.h"

#define USART2_RX_Pin LL_GPIO_PIN_3
#define USART2_RX_GPIO_Port GPIOA

#endif /* MAIN_H_ */
