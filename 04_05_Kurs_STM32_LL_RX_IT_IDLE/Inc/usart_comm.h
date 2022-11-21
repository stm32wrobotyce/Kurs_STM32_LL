/*
 * usart_comm.h
 *
 *  Created on: 14 lis 2022
 *      Author: piotr
 */

#ifndef USART_COMM_H_
#define USART_COMM_H_

#include "main.h"

#define BUFFER_SIZE	128

typedef struct
{
	uint8_t data[BUFFER_SIZE];
	uint32_t count;
}buffer_t;

void usart_it_rx_not_empty_callback(void);

#endif /* USART_COMM_H_ */
