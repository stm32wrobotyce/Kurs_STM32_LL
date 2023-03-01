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
#include "stm32g0xx_ll_i2c.h"
#include "stm32g0xx_ll_spi.h"
#include "stm32g0xx_ll_dma.h"
#include "stm32g0xx_ll_dmamux.h"

#include "software_timer.h"
#include "spi.h"

#define RST_Pin 			LL_GPIO_PIN_0
#define RST_GPIO_Port 		GPIOC

#define DC_Pin 				LL_GPIO_PIN_1
#define DC_GPIO_Port 		GPIOC

#define BUSY_Pin 			LL_GPIO_PIN_2
#define BUSY_GPIO_Port 		GPIOC

#define SPI_CS_Pin 			LL_GPIO_PIN_4
#define SPI_CS_GPIO_Port 	GPIOA

#define SPI_MOSI_Pin		LL_GPIO_PIN_7
#define SPI_MOSI_GPIO_Port 	GPIOA

#define SPI_MISO_Pin		LL_GPIO_PIN_6
#define SPI_MISO_GPIO_Port 	GPIOA

#define SPI_SCK_Pin 		LL_GPIO_PIN_1
#define SPI_SCK_GPIO_Port 	GPIOA

void rcc_init(void);

#endif /* MAIN_H_ */
