/*
 * adc.c
 *
 *  Created on: 15 lis 2022
 *      Author: piotr
 */

#include "adc.h"

#define ADC_VREF_MV		3300
#define ADC_MAX_VALUE	4096
#define CONVERT_ADC_TO_MV(x) ((ADC_VREF_MV * x) / (ADC_MAX_VALUE - 1))

#define NUMBER_OF_CONVERSION	3

uint32_t adc_data[NUMBER_OF_CONVERSION] = {0};
uint32_t voltage_mv[NUMBER_OF_CONVERSION] = {0};

void adc_start_dma_conversion(void)
{
	LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_1, LL_ADC_DMA_GetRegAddr(ADC1, LL_ADC_DMA_REG_REGULAR_DATA), (uint32_t)adc_data, LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1));
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, NUMBER_OF_CONVERSION);

	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
}

void dma_transfer_complete_callback(void)
{
	for (int i = 0; i < NUMBER_OF_CONVERSION; ++i)
	{
		voltage_mv[i] = CONVERT_ADC_TO_MV(adc_data[i]);
	}
}
