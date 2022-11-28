/*
 * usart_comm.h
 *
 *  Created on: 14 lis 2022
 *      Author: piotr
 */

#ifndef USART_COMM_H_
#define USART_COMM_H_

#include "main.h"

#define BUFFER_SIZE	12	//Length of test frame "Receive Test"

typedef struct
{
	uint8_t data[BUFFER_SIZE];
	uint32_t count;
}buffer_t;

void receive_data_init(void);
void receive_data_DMA(uint8_t *data_buf, uint32_t data_size);
void DMA1_receive_complete_callback(void);

#endif /* USART_COMM_H_ */
