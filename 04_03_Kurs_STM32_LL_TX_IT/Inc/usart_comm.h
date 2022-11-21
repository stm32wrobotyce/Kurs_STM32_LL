/*
 * usart_comm.h
 *
 *  Created on: 14 lis 2022
 *      Author: piotr
 */

#ifndef USART_COMM_H_
#define USART_COMM_H_

#include "main.h"

void transmit_task_init(void);
void transmit_task_process(void);
void transmit_data(uint8_t *data_buf, uint32_t data_size);
void usart_it_tx_empty_callback(void);

#endif /* USART_COMM_H_ */
