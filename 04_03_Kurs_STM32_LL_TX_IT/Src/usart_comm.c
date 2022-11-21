/*
 * usart_comm.c
 *
 *  Created on: 14 lis 2022
 *      Author: piotr
 */


#include "usart_comm.h"

#define TRANSMIT_TASK_TIME	1000

software_timer_t tx_timer;

const uint8_t tx_buffer[6] = {"TEST\n\r"};
volatile uint32_t tx_buffer_count = 0;

void transmit_task_init(void)
{
	software_timer_task_init(&tx_timer, TRANSMIT_TASK_TIME);
}

void transmit_task_process(void)
{
	if((software_timer_get_ms_tick() - tx_timer.ms_tick) >= tx_timer.task_time)
	{
		tx_timer.ms_tick = software_timer_get_ms_tick();

		LL_USART_EnableIT_TXE(USART2);
	}
}

void transmit_data(uint8_t *data_buf, uint32_t data_size)
{
	for (int var = 0; var < data_size; ++var)
	{
		  while (!LL_USART_IsActiveFlag_TXE(USART2))
			  ;

		  LL_USART_TransmitData8(USART2, data_buf[var]);
	}
}

void usart_it_tx_empty_callback(void)
{
	if(tx_buffer_count == sizeof(tx_buffer))
	{
		tx_buffer_count = 0;
		LL_USART_DisableIT_TXE(USART2);

		return;
	}

	LL_USART_TransmitData8(USART2, tx_buffer[tx_buffer_count]);
	tx_buffer_count++;
}
