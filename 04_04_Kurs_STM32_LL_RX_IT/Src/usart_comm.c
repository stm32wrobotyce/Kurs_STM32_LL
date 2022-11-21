/*
 * usart_comm.c
 *
 *  Created on: 14 lis 2022
 *      Author: piotr
 */


#include "usart_comm.h"

#define TRANSMIT_TASK_TIME	1000

software_timer_t tx_timer;

buffer_t rx_buffer = {0};

void usart_it_rx_not_empty_callback(void)
{
	rx_buffer.data[rx_buffer.count] = LL_USART_ReceiveData8(USART2);
	rx_buffer.count++;
}
