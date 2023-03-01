/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>

#include "main.h"

#include "DEV_Config.h"
#include "EPD_1in54b.h"
#include "GUI_Paint.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#define SPI_TASK_TIME	1000
#define IMAGE_SIZE_EPD_200_200_PX	5000	//(200 px * 200 px) / 8 bitów

static software_timer_t spi_timer;

extern const unsigned char logo[];
uint8_t black_image[IMAGE_SIZE_EPD_200_200_PX];
uint8_t red_image[IMAGE_SIZE_EPD_200_200_PX];

int main(void)
{
	rcc_init();

	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOC);

	LL_GPIO_SetPinOutputType(RST_GPIO_Port, RST_Pin, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(RST_GPIO_Port, RST_Pin, LL_GPIO_PULL_NO);
	LL_GPIO_SetPinSpeed(RST_GPIO_Port, RST_Pin, LL_GPIO_SPEED_FREQ_LOW);
	LL_GPIO_SetPinMode(RST_GPIO_Port, RST_Pin, LL_GPIO_MODE_OUTPUT);

	LL_GPIO_SetPinOutputType(DC_GPIO_Port, DC_Pin, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(DC_GPIO_Port, DC_Pin, LL_GPIO_PULL_NO);
	LL_GPIO_SetPinSpeed(DC_GPIO_Port, DC_Pin, LL_GPIO_SPEED_FREQ_LOW);
	LL_GPIO_SetPinMode(DC_GPIO_Port, DC_Pin, LL_GPIO_MODE_OUTPUT);

	LL_GPIO_SetPinPull(BUSY_GPIO_Port, BUSY_Pin, LL_GPIO_PULL_NO);
	LL_GPIO_SetPinSpeed(BUSY_GPIO_Port, BUSY_Pin, LL_GPIO_SPEED_FREQ_LOW);
	LL_GPIO_SetPinMode(BUSY_GPIO_Port, BUSY_Pin, LL_GPIO_MODE_INPUT);

	spi_init();

	DEV_Module_Init();

	EPD_1IN54B_Init();
	EPD_1IN54B_Clear();

	uint8_t *BlackImage, *RedImage;

	BlackImage = black_image;
	RedImage = red_image;

    Paint_NewImage(BlackImage, EPD_1IN54B_WIDTH, EPD_1IN54B_HEIGHT, ROTATE_270, WHITE);
    Paint_NewImage(RedImage, EPD_1IN54B_WIDTH, EPD_1IN54B_HEIGHT, ROTATE_270, WHITE);

    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);
    Paint_DrawBitMap(logo);

    Paint_SelectImage(RedImage);
    Paint_Clear(WHITE);
    Paint_DrawString_EN(5, 175, "stm32wrobotyce.pl", &Font16, WHITE, BLACK);

    EPD_1IN54B_Display(BlackImage, RedImage);

	software_timer_task_init(&spi_timer, SPI_TASK_TIME);

	while (1)
	{
		  if((software_timer_get_ms_tick() - spi_timer.ms_tick) >= spi_timer.task_time)
		  {
			  	spi_timer.ms_tick = software_timer_get_ms_tick();

		  }
	}
}

void rcc_init(void)
{
	LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);

	LL_RCC_HSI_Enable();
	while(LL_RCC_HSI_IsReady() != 1)
		;

	LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_1, 8, LL_RCC_PLLR_DIV_2);

	LL_RCC_PLL_Enable();
	while(LL_RCC_PLL_IsReady() != 1)
		;

	LL_RCC_PLL_EnableDomain_SYS();

	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);

	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
	while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
		;

	LL_SetSystemCoreClock(64000000);
	LL_Init1msTick(64000000);
	LL_SYSTICK_EnableIT();
}
