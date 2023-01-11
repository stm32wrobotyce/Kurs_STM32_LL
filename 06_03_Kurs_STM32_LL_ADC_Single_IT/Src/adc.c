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

volatile uint32_t adc_data = 0;
volatile uint32_t voltage_mv = 0;

void adc_conversion_complete_callback(void)
{
	  adc_data = LL_ADC_REG_ReadConversionData12(ADC1);

	  voltage_mv = CONVERT_ADC_TO_MV(adc_data);
}
