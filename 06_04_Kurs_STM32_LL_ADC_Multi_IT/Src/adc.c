/*
 * adc.c
 *
 *  Created on: 15 lis 2022
 *      Author: piotr
 */

#include "adc.h"

#define	NUMBER_OF_CONVERSION	3

#define ADC_VREF_MV		3300
#define ADC_MAX_VALUE	4096
#define CONVERT_ADC_TO_MV(x) ((ADC_VREF_MV * x) / (ADC_MAX_VALUE - 1))

volatile uint32_t adc_data[NUMBER_OF_CONVERSION] = {0};
volatile uint32_t voltage_mv[NUMBER_OF_CONVERSION] = {0};
volatile uint32_t conv_cnt = 0;

void adc_conversion_complete_callback(void)
{
	  adc_data[conv_cnt] = LL_ADC_REG_ReadConversionData12(ADC1);
	  voltage_mv[conv_cnt] = CONVERT_ADC_TO_MV(adc_data[conv_cnt]);

	  conv_cnt++;
}

void adc_sequence_complete_callback(void)
{
	conv_cnt = 0;
}
