/*
 * usart_comm.c
 *
 *  Created on: 14 lis 2022
 *      Author: piotr
 */


#include "usart_comm.h"

buffer_t rx_buffer = {0};

void receive_data_init(void)
{
	receive_data_DMA(rx_buffer.data, sizeof(rx_buffer.data));
}

void receive_data_DMA(uint8_t *data_buf, uint32_t data_size)
{
	LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_1, LL_USART_DMA_GetRegAddr(USART2, LL_USART_DMA_REG_DATA_RECEIVE), (uint32_t)data_buf, LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1));
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, data_size);

	LL_USART_EnableDMAReq_RX(USART2);
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
}

void DMA1_receive_complete_callback(void)
{
	LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_1);

	receive_data_init();
}
