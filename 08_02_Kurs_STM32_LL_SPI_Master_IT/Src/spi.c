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

	NVIC_SetPriority(SPI1_IRQn, 1);
	NVIC_EnableIRQ(SPI1_IRQn);
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

void spi_write_data_it(uint8_t *data, uint32_t size)
{
	tx_buffer.data_ptr = data;
	tx_buffer.count = size;

	LL_SPI_EnableIT_TXE(spi);
	LL_SPI_Enable(spi);
}

void spi_read_data_it(uint8_t *data, uint32_t size)
{
	tx_buffer.count = size;

	rx_buffer.data_ptr = data;
	rx_buffer.count = size;

	LL_SPI_EnableIT_TXE(spi);
	LL_SPI_EnableIT_RXNE(spi);
	LL_SPI_Enable(spi);
}

void spi_it_transmit_callback(void)
{
	if(tx_buffer.count > 0)
	{
		if(!LL_SPI_IsEnabledIT_RXNE(spi))
		{
			LL_SPI_TransmitData8(spi, *tx_buffer.data_ptr);

			tx_buffer.data_ptr++;
			tx_buffer.count--;
		}
		else
		{
			LL_SPI_TransmitData8(spi, DUMMY_BYTE);
			tx_buffer.count--;
		}
	}

	if(tx_buffer.count <= 0 && !LL_SPI_IsEnabledIT_RXNE(spi))
	{
		LL_SPI_DisableIT_TXE(spi);

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

void spi_it_receive_callback(void)
{
	if(rx_buffer.count > 0)
	{
		*rx_buffer.data_ptr = LL_SPI_ReceiveData8(spi);

		rx_buffer.data_ptr++;
		rx_buffer.count--;
	}

	if(rx_buffer.count <= 0)
	{
		LL_SPI_DisableIT_RXNE(spi);
		LL_SPI_DisableIT_TXE(spi);

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
}

__attribute__((weak)) void spi_transfer_cplt_callback(transfer_type_t type)
{
	(void)type;
}
