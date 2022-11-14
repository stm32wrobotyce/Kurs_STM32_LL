/*
 * usart_comm.c
 *
 *  Created on: 14 lis 2022
 *      Author: piotr
 */


#include "usart_comm.h"

#define TRANSMIT_TASK_TIME	1000

software_timer_t tx_timer;

void transmit_task_init(void)
{
	software_timer_task_init(&tx_timer, TRANSMIT_TASK_TIME);
}

void transmit_task_process(void)
{
	uint8_t tx_buffer[6] = {"TEST\n\r"};

	if((software_timer_get_ms_tick() - tx_timer.ms_tick) >= tx_timer.task_time)
	{
		tx_timer.ms_tick = software_timer_get_ms_tick();

		transmit_data(tx_buffer, sizeof(tx_buffer));
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
