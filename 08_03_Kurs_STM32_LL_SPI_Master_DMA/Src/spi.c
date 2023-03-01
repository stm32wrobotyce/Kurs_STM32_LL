/*
 * spi.c
 *
 *  Created on: 12 sty 2023
 *      Author: piotr
 */

#include "spi.h"

#define DUMMY_BYTE 0xFF

SPI_TypeDef * spi = SPI1;

static buffer_t rx_buffer = {0};
static buffer_t tx_buffer = {0};

void spi_init(void)
{
	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

	LL_GPIO_SetPinOutputType(SPI_MOSI_GPIO_Port, SPI_MOSI_Pin, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(SPI_MOSI_GPIO_Port, SPI_MOSI_Pin, LL_GPIO_PULL_NO);
	LL_GPIO_SetPinSpeed(SPI_MOSI_GPIO_Port, SPI_MOSI_Pin, LL_GPIO_SPEED_FREQ_LOW);
	LL_GPIO_SetAFPin_0_7(SPI_MOSI_GPIO_Port, SPI_MOSI_Pin, LL_GPIO_AF_0);
	LL_GPIO_SetPinMode(SPI_MOSI_GPIO_Port, SPI_MOSI_Pin, LL_GPIO_MODE_ALTERNATE);

	LL_GPIO_SetPinOutputType(SPI_MISO_GPIO_Port, SPI_MISO_Pin, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(SPI_MISO_GPIO_Port, SPI_MISO_Pin, LL_GPIO_PULL_NO);
	LL_GPIO_SetPinSpeed(SPI_MISO_GPIO_Port, SPI_MISO_Pin, LL_GPIO_SPEED_FREQ_LOW);
	LL_GPIO_SetAFPin_0_7(SPI_MISO_GPIO_Port, SPI_MISO_Pin, LL_GPIO_AF_0);
	LL_GPIO_SetPinMode(SPI_MISO_GPIO_Port, SPI_MISO_Pin, LL_GPIO_MODE_ALTERNATE);

	LL_GPIO_SetPinOutputType(SPI_SCK_GPIO_Port, SPI_SCK_Pin, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(SPI_SCK_GPIO_Port, SPI_SCK_Pin, LL_GPIO_PULL_NO);
	LL_GPIO_SetPinSpeed(SPI_SCK_GPIO_Port, SPI_SCK_Pin, LL_GPIO_SPEED_FREQ_LOW);
	LL_GPIO_SetAFPin_0_7(SPI_SCK_GPIO_Port, SPI_SCK_Pin, LL_GPIO_AF_0);
	LL_GPIO_SetPinMode(SPI_SCK_GPIO_Port, SPI_SCK_Pin, LL_GPIO_MODE_ALTERNATE);

	LL_GPIO_SetPinOutputType(SPI_CS_GPIO_Port, SPI_CS_Pin, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(SPI_CS_GPIO_Port, SPI_CS_Pin, LL_GPIO_PULL_NO);
	LL_GPIO_SetPinSpeed(SPI_CS_GPIO_Port, SPI_CS_Pin, LL_GPIO_SPEED_FREQ_LOW);
	LL_GPIO_SetPinMode(SPI_CS_GPIO_Port, SPI_CS_Pin, LL_GPIO_MODE_OUTPUT);

	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);

	LL_SPI_Disable(spi);

	LL_SPI_SetMode(spi, LL_SPI_MODE_MASTER);
	LL_SPI_SetTransferDirection(spi, LL_SPI_FULL_DUPLEX);
	LL_SPI_SetClockPolarity(spi, LL_SPI_POLARITY_LOW);
	LL_SPI_SetClockPhase(spi, LL_SPI_PHASE_1EDGE);
	LL_SPI_SetNSSMode(spi, LL_SPI_NSS_SOFT);
	LL_SPI_SetBaudRatePrescaler(spi, LL_SPI_BAUDRATEPRESCALER_DIV8);
	LL_SPI_SetTransferBitOrder(spi, LL_SPI_MSB_FIRST);
	LL_SPI_SetDataWidth(spi, LL_SPI_DATAWIDTH_8BIT);
	LL_SPI_SetStandard(spi, LL_SPI_PROTOCOL_MOTOROLA);
	LL_SPI_SetRxFIFOThreshold(spi, LL_SPI_RX_FIFO_TH_QUARTER);

	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

	LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_1, LL_DMAMUX_REQ_SPI1_TX);
	LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
	LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PRIORITY_HIGH);
	LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MODE_NORMAL);
	LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PERIPH_NOINCREMENT);
	LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MEMORY_INCREMENT);
	LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PDATAALIGN_BYTE);
	LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MDATAALIGN_BYTE);

	NVIC_SetPriority(DMA1_Channel1_IRQn, 0);
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
	LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_1);

	LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_2, LL_DMAMUX_REQ_SPI1_RX);
	LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_2, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
	LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_2, LL_DMA_PRIORITY_HIGH);
	LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MODE_NORMAL);
	LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_PERIPH_NOINCREMENT);
	LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MEMORY_INCREMENT);
	LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_2, LL_DMA_PDATAALIGN_BYTE);
	LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MDATAALIGN_BYTE);

	NVIC_SetPriority(DMA1_Channel2_3_IRQn, 0);
	NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);
	LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_2);
}

void spi_cs_set_high(void)
{
	LL_GPIO_SetOutputPin(SPI_CS_GPIO_Port, SPI_CS_Pin);
}

void spi_cs_set_low(void)
{
	LL_GPIO_ResetOutputPin(SPI_CS_GPIO_Port, SPI_CS_Pin);
}

void spi_write_data(uint8_t *data, uint32_t size)
{
	uint32_t count = 0;

	LL_SPI_Enable(spi);

	while(count < size)
	{
		while (!LL_SPI_IsActiveFlag_TXE(spi))
			;

		LL_SPI_TransmitData8(spi, *(data+count));

		count++;
	}

	while (LL_SPI_GetTxFIFOLevel(spi) != LL_SPI_TX_FIFO_EMPTY)
		;

	while (LL_SPI_IsActiveFlag_BSY(spi) != 0)
		;

	LL_SPI_Disable(spi);

	while (LL_SPI_GetRxFIFOLevel(spi) != LL_SPI_RX_FIFO_EMPTY)
	{
		LL_SPI_ReceiveData8(spi);
	}

	LL_SPI_ClearFlag_OVR(spi);
}

void spi_read_data(uint8_t *data, uint32_t size)
{
	uint32_t count = 0;

	LL_SPI_Enable(spi);

	while(count < size)
	{
		while (!LL_SPI_IsActiveFlag_TXE(spi))
			;

		LL_SPI_TransmitData8(spi, DUMMY_BYTE);

		while (!LL_SPI_IsActiveFlag_RXNE(spi))
			;

		*(data+count) = LL_SPI_ReceiveData8(spi);

		count++;
	}

	while (LL_SPI_GetTxFIFOLevel(spi) != LL_SPI_TX_FIFO_EMPTY)
		;

	while (LL_SPI_IsActiveFlag_BSY(spi) != 0)
		;

	LL_SPI_Disable(spi);

	while (LL_SPI_GetRxFIFOLevel(spi) != LL_SPI_RX_FIFO_EMPTY)
	{
		LL_SPI_ReceiveData8(spi);
	}

	LL_SPI_ClearFlag_OVR(spi);
}

void spi_write_data_dma(uint8_t *data, uint32_t size)
{
	tx_buffer.data_ptr = data;
	tx_buffer.count = size;

	LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_1, (uint32_t)tx_buffer.data_ptr, LL_SPI_DMA_GetRegAddr(SPI1), LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1));
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, tx_buffer.count);

	LL_SPI_EnableDMAReq_TX(SPI1);
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
	LL_SPI_Enable(spi);
}

void spi_read_data_dma(uint8_t *data, uint32_t size)
{
	tx_buffer.data_ptr = data;
	tx_buffer.count = size;

	rx_buffer.data_ptr = data;
	rx_buffer.count = size;

	LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_1, (uint32_t)tx_buffer.data_ptr, LL_SPI_DMA_GetRegAddr(spi), LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1));
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, tx_buffer.count);

	LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_2, LL_SPI_DMA_GetRegAddr(spi), (uint32_t)rx_buffer.data_ptr, LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_2));
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_2, rx_buffer.count);

	LL_SPI_EnableDMAReq_TX(spi);
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);

	LL_SPI_EnableDMAReq_RX(spi);
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_2);

	LL_SPI_Enable(spi);
}

void spi_dma_transmit_callback(void)
{
	LL_SPI_DisableDMAReq_TX(SPI1);
	LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_1);

	if(!LL_SPI_IsEnabledDMAReq_RX(spi))
	{
		while (LL_SPI_GetTxFIFOLevel(spi) != LL_SPI_TX_FIFO_EMPTY)
			;

		while (LL_SPI_IsActiveFlag_BSY(spi) != 0)
			;

		LL_SPI_Disable(spi);

		while (LL_SPI_GetRxFIFOLevel(spi) != LL_SPI_RX_FIFO_EMPTY)
		{
			LL_SPI_ReceiveData8(spi);
		}

		LL_SPI_ClearFlag_OVR(spi);

		spi_cs_set_high();
		spi_transfer_cplt_callback(TRANSMIT);
	}
}

void spi_dma_receive_callback(void)
{
	LL_SPI_DisableDMAReq_RX(SPI1);
	LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_2);

	while (LL_SPI_GetTxFIFOLevel(spi) != LL_SPI_TX_FIFO_EMPTY)
		;

	while (LL_SPI_IsActiveFlag_BSY(spi) != 0)
		;

	LL_SPI_Disable(spi);

	while (LL_SPI_GetRxFIFOLevel(spi) != LL_SPI_RX_FIFO_EMPTY)
	{
		LL_SPI_ReceiveData8(spi);
	}

	LL_SPI_ClearFlag_OVR(spi);

	spi_cs_set_high();
	spi_transfer_cplt_callback(RECEIVE);
}

__attribute__((weak)) void spi_transfer_cplt_callback(transfer_type_t type)
{
	(void)type;
}
