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

		LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_1, (uint32_t)tx_buffer, LL_USART_DMA_GetRegAddr(USART2, LL_USART_DMA_REG_DATA_TRANSMIT), LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1));
		LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, sizeof(tx_buffer));

		LL_USART_EnableDMAReq_TX(USART2);
		LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
	}
}

void DMA1_transmit_complete_callback()
{
	LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_1);
}
