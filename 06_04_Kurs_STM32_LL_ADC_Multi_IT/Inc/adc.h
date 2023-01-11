/*
 * adc.h
 *
 *  Created on: 15 lis 2022
 *      Author: piotr
 */

#ifndef ADC_H_
#define ADC_H_

#include "main.h"

#define ADC_TASK_TIME	100

void adc_conversion_complete_callback(void);
void adc_sequence_complete_callback(void);

#endif /* ADC_H_ */
