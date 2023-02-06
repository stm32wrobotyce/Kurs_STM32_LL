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
#include "stm32g0xx_ll_dma.h"
#include "stm32g0xx_ll_dmamux.h"

#include "i2c.h"

#include "software_timer.h"

#define I2C1_SDA_Pin LL_GPIO_PIN_9
#define I2C1_SDA_GPIO_Port GPIOB

#define I2C1_SCL_Pin LL_GPIO_PIN_8
#define I2C1_SCL_GPIO_Port GPIOB

void rcc_init(void);

#endif /* MAIN_H_ */
