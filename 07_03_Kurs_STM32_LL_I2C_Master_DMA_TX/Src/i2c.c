/*
 * i2c.c
 *
 *  Created on: 30 lis 2022
 *      Author: piotr
 */

#include "i2c.h"

I2C_TypeDef *i2c = I2C1;

static buffer_t tx_buffer = {0};

int32_t i2c_init(void)
{
	//GPIO
	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);

	LL_GPIO_SetPinSpeed(I2C1_SCL_GPIO_Port, I2C1_SCL_Pin, LL_GPIO_SPEED_FREQ_LOW);
	LL_GPIO_SetPinOutputType(I2C1_SCL_GPIO_Port, I2C1_SCL_Pin, LL_GPIO_OUTPUT_OPENDRAIN);
	LL_GPIO_SetPinPull(I2C1_SCL_GPIO_Port, I2C1_SCL_Pin, LL_GPIO_PULL_NO);
	LL_GPIO_SetAFPin_8_15(I2C1_SCL_GPIO_Port, I2C1_SCL_Pin, LL_GPIO_AF_6);
	LL_GPIO_SetPinMode(I2C1_SCL_GPIO_Port, I2C1_SCL_Pin, LL_GPIO_MODE_ALTERNATE);

	LL_GPIO_SetPinOutputType(I2C1_SDA_GPIO_Port, I2C1_SDA_Pin, LL_GPIO_OUTPUT_OPENDRAIN);
	LL_GPIO_SetPinPull(I2C1_SDA_GPIO_Port, I2C1_SDA_Pin, LL_GPIO_PULL_NO);
	LL_GPIO_SetPinSpeed(I2C1_SDA_GPIO_Port, I2C1_SDA_Pin, LL_GPIO_SPEED_FREQ_VERY_HIGH);
	LL_GPIO_SetAFPin_8_15(I2C1_SDA_GPIO_Port, I2C1_SDA_Pin, LL_GPIO_AF_6);
	LL_GPIO_SetPinMode(I2C1_SDA_GPIO_Port, I2C1_SDA_Pin, LL_GPIO_MODE_ALTERNATE);

	//DMA
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

	LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_1, LL_DMAMUX_REQ_I2C1_TX);
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

	//I2C
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);

	LL_I2C_Disable(i2c);
	LL_I2C_ConfigFilters(i2c, LL_I2C_ANALOGFILTER_ENABLE, 0x00);
	LL_I2C_SetTiming(i2c, 0x10707DBC);
	LL_I2C_EnableClockStretching(i2c);
	LL_I2C_SetMode(i2c, LL_I2C_MODE_I2C);
	LL_I2C_Enable(i2c);

	return 0;
}

int32_t i2c_reg_write(uint16_t slave_addr, uint16_t reg_addr, uint8_t *data_ptr, uint16_t size)
{
	uint8_t data_count = size;

	LL_I2C_HandleTransfer(i2c, slave_addr, LL_I2C_ADDRSLAVE_7BIT, (uint32_t)(size+1), LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE);

	while(LL_I2C_IsActiveFlag_TXIS(i2c) == 0)
		;

	LL_I2C_TransmitData8(i2c, (uint8_t)reg_addr);

	while(data_count > 0)
	{
		while(LL_I2C_IsActiveFlag_TXIS(i2c) == 0)
			;

		LL_I2C_TransmitData8(i2c, *data_ptr);

		data_ptr++;
		data_count--;
	}

	while(LL_I2C_IsActiveFlag_STOP(i2c) == 0)
		;

	LL_I2C_ClearFlag_STOP(i2c);

	return 0;
}

int32_t i2c_reg_read(uint16_t slave_addr, uint16_t reg_addr, uint8_t *read_data_ptr, uint16_t read_size)
{
	uint8_t read_data_count = read_size;

	LL_I2C_HandleTransfer(i2c, slave_addr, LL_I2C_ADDRSLAVE_7BIT, 1, LL_I2C_MODE_SOFTEND, LL_I2C_GENERATE_START_WRITE);

	while(LL_I2C_IsActiveFlag_TXIS(i2c) == 0)
		;

	LL_I2C_TransmitData8(i2c, (uint8_t)reg_addr);

	while(LL_I2C_IsActiveFlag_TC(i2c) == 0)
		;

	LL_I2C_HandleTransfer(i2c, slave_addr, LL_I2C_ADDRSLAVE_7BIT, (uint32_t)read_size, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_READ);

	while(read_data_count > 0)
	{
		while(LL_I2C_IsActiveFlag_RXNE(i2c) == 0)
			;

		*read_data_ptr = LL_I2C_ReceiveData8(i2c);

		read_data_ptr++;
		read_data_count--;
	}

	while(LL_I2C_IsActiveFlag_STOP(i2c) == 0)
		;

	LL_I2C_ClearFlag_STOP(i2c);

	return 0;
}

int32_t i2c_reg_write_dma(uint16_t slave_addr, uint16_t reg_addr, uint8_t *data_ptr, uint16_t size)
{
	tx_buffer.data_ptr = data_ptr;
	tx_buffer.count = size;

	LL_I2C_HandleTransfer(i2c, slave_addr, LL_I2C_ADDRSLAVE_7BIT, (uint32_t)(size+1), LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE);

	while(LL_I2C_IsActiveFlag_TXIS(i2c) == 0)
		;

	LL_I2C_TransmitData8(i2c, (uint8_t)reg_addr);

	LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_1, (uint32_t)tx_buffer.data_ptr, LL_I2C_DMA_GetRegAddr(I2C1, LL_I2C_DMA_REG_DATA_TRANSMIT), LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1));
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, tx_buffer.count);

	LL_I2C_EnableDMAReq_TX(I2C1);
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);

	return 0;
}

void DMA1_transmit_complete_callback(void)
{
	LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_1);
	LL_I2C_ClearFlag_STOP(i2c);
}
