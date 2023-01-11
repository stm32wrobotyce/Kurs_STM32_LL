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
#include "stm32g0xx_ll_adc.h"

#include "software_timer.h"
#include "adc.h"

#define LED_GREEN_Pin LL_GPIO_PIN_5
#define LED_GREEN_GPIO_Port GPIOA

#define ADC_Pot3_Pin LL_GPIO_PIN_4
#define ADC_Pot3_GPIO_Port GPIOA

#define ADC_Pot2_Pin LL_GPIO_PIN_1
#define ADC_Pot2_GPIO_Port GPIOA

#define ADC_Pot1_Pin LL_GPIO_PIN_0
#define ADC_Pot1_GPIO_Port GPIOA

#endif /* MAIN_H_ */
