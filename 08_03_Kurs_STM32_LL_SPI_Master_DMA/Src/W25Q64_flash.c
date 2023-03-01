/*
 * W25Q64_Flash.c
 *
 *  Created on: Oct 28, 2021
 *      Author: piotr
 */

#include "W25Q64_flash.h"

#define OK		0
#define ERROR	1

#define W25Q64_WRITE_IN_PROGRESS  	0x01
#define W25Q64_WRITE_ENABLE_LATCH 	0x02

#define WRITE_ENABLE				0x06
#define WRITE_DISABLE				0x04
#define READ_STATUS_REG1			0x05
#define READ_STATUS_REG2			0x35
#define WRITE_STATUS_REG			0x01
#define READ_DATA					0x03
#define PAGE_PROGRAM				0x02
#define SECTOR_ERASE				0x20
#define CHIP_ERASE					0xC7
#define ENABLE_RESET				0x66
#define RESET						0x99

#define	WIBOND_ID					0xEF
#define SPI_DEVICE_ID				0x40
#define CAPACITY_64_MBIT			0x17

uint8_t W25Q64_Init()
{
	struct memory_info w25q64_memory;

	W25Q64_ResetFlash();
	W25Q64_get_JEDEC_ID(&w25q64_memory);

	if(WIBOND_ID == w25q64_memory.manufacturer_ID && SPI_DEVICE_ID == w25q64_memory.memory_type && CAPACITY_64_MBIT == w25q64_memory.capacity)
		return OK;
	else
		return ERROR;
}

void W25Q64_ResetFlash(void)
{
	uint8_t data_to_send[] = { ENABLE_RESET, RESET };

	W25Q64_Set_ChipSelect_Low();
	W25Q64_SPI_Transmit_Data(data_to_send, 2);
	W25Q64_Set_ChipSelect_High();
}

void W25Q64_WriteEnable(void)
{
	uint8_t data_to_send =  WRITE_ENABLE;

	W25Q64_Set_ChipSelect_Low();
	W25Q64_SPI_Transmit_Data(&data_to_send, 1);
	W25Q64_Set_ChipSelect_High();
}

void W25Q64_write_disable(void)
{
	uint8_t data_to_send =  WRITE_DISABLE;

	W25Q64_Set_ChipSelect_Low();
	W25Q64_SPI_Transmit_Data(&data_to_send, 1);
	W25Q64_Set_ChipSelect_High();
}

uint8_t W25Q64_ReadStatusRegister1(void)
{
	uint8_t data_to_send = READ_STATUS_REG1;
	uint8_t receive_data = 0;

	W25Q64_Set_ChipSelect_Low();
	W25Q64_SPI_Transmit_Data(&data_to_send, 1);
	W25Q64_SPI_Receive_Data(&receive_data, 1);
	W25Q64_Set_ChipSelect_High();

	return receive_data;
}

uint8_t W25Q64_ReadStatusRegister2(void)
{
	uint8_t data_to_send = READ_STATUS_REG2;
	uint8_t receive_data = 0;

	W25Q64_Set_ChipSelect_Low();
	W25Q64_SPI_Transmit_Data(&data_to_send, 1);
	W25Q64_SPI_Receive_Data(&receive_data, 1);
	W25Q64_Set_ChipSelect_High();

	return receive_data;
}

void W25Q64_WriteStatusRegister(uint8_t reg1, uint8_t reg2)
{
	uint8_t data_to_send[] = { 0, 0, 0 };

	W25Q64_WriteEnable_and_WaitForWriteEnableLatch();

	data_to_send[0] = WRITE_STATUS_REG;
	data_to_send[1] = reg1;
	data_to_send[2] = reg2;

	W25Q64_Set_ChipSelect_Low();
	W25Q64_SPI_Transmit_Data(data_to_send, 2);
	W25Q64_Set_ChipSelect_High();
}

uint8_t W25Q64_ReadDataBytes(uint32_t adress, uint8_t *data, uint16_t size)
{
	uint8_t data_to_send[] = { 0, 0, 0, 0 };
	uint8_t status;

	W25Q64_WaitForWriteInProgressClear();

	data_to_send[0] = READ_DATA;
	data_to_send[1] = (adress >> 16) & 0xff;
	data_to_send[2] = (adress >> 8) & 0xff;
	data_to_send[3] = adress & 0xff;

	W25Q64_Set_ChipSelect_Low();
	W25Q64_SPI_Transmit_Data(data_to_send, 4);
	status = W25Q64_SPI_Receive_Data_DMA(data, size);
	//W25Q64_Set_ChipSelect_High();

	return status;
}

uint8_t W25Q64_PageProgram(uint32_t page_adress, uint8_t *data, uint16_t size)
{
	uint8_t data_to_send[] = { 0, 0, 0, 0 };
	uint8_t status;

	W25Q64_WaitForWriteInProgressClear();
	W25Q64_WriteEnable_and_WaitForWriteEnableLatch();

	data_to_send[0] = PAGE_PROGRAM;
	data_to_send[1] = (page_adress >> 16) & 0xff;
	data_to_send[2] = (page_adress >> 8) & 0xff;
	data_to_send[3] = page_adress & 0xff;

	W25Q64_Set_ChipSelect_Low();
	W25Q64_SPI_Transmit_Data(data_to_send, 4);
	status = W25Q64_SPI_Transmit_Data_DMA(data, size);
	//W25Q64_Set_ChipSelect_High();

	return status;
}

uint8_t W25Q64_SectorErase(uint16_t sector_number)
{
	uint32_t adress;
	adress = sector_number * SECTOR_SIZE;
	uint8_t data_to_send[] = { 0, 0, 0, 0 };
	uint8_t status;

	W25Q64_WaitForWriteInProgressClear();
	W25Q64_WriteEnable_and_WaitForWriteEnableLatch();

	data_to_send[0] = SECTOR_ERASE;
	data_to_send[1] = (adress >> 16) & 0xff;
	data_to_send[2] = (adress >> 8) & 0xff;
	data_to_send[3] = adress & 0xff;

	W25Q64_Set_ChipSelect_Low();
	status = W25Q64_SPI_Transmit_Data(data_to_send, 4);
	W25Q64_Set_ChipSelect_High();

	W25Q64_WaitForWriteInProgressClear();

	return status;
}

uint8_t W25Q64_ChipErase(void)
{
	uint8_t data_to_send =  CHIP_ERASE;
	uint8_t status;

	W25Q64_WaitForWriteInProgressClear();
	W25Q64_WriteEnable_and_WaitForWriteEnableLatch();

	W25Q64_Set_ChipSelect_Low();
	status = W25Q64_SPI_Transmit_Data(&data_to_send, 1);
	W25Q64_Set_ChipSelect_High();

	W25Q64_WaitForWriteInProgressClear();

	return status;
}

void W25Q64_get_JEDEC_ID(struct memory_info *info)
{
	uint8_t data_to_send = 0x9F;
	uint8_t receive_data[3] = { 0, 0, 0 };

	W25Q64_Set_ChipSelect_Low();

	W25Q64_SPI_Transmit_Data(&data_to_send, 1);
	W25Q64_SPI_Receive_Data(receive_data, 3);

	W25Q64_Set_ChipSelect_High();

	info->manufacturer_ID = receive_data[0];
	info->memory_type = receive_data[1];
	info->capacity = receive_data[2];
}

void W25Q64_WriteEnable_and_WaitForWriteEnableLatch(void)
{
	while(!(W25Q64_ReadStatusRegister1() & W25Q64_WRITE_ENABLE_LATCH))
	{
		W25Q64_WriteEnable();
	}
}

void W25Q64_WaitForWriteEnableLatch(void)
{
	while(!(W25Q64_ReadStatusRegister1() & W25Q64_WRITE_ENABLE_LATCH))
	{
		;
	}
}

void W25Q64_WaitForWriteInProgressClear(void)
{
	while((W25Q64_ReadStatusRegister1() & W25Q64_WRITE_IN_PROGRESS))
	{
		;
	}
}

uint8_t W25Q64_SPI_Transmit_Data(uint8_t *data, uint16_t size)
{
	uint8_t status = 0;

	spi_write_data(data, size);

	return status;
}

uint8_t W25Q64_SPI_Receive_Data(uint8_t *data, uint16_t size)
{
	uint8_t status = 0;

	spi_read_data(data, size);

	return status;
}

uint8_t W25Q64_SPI_Transmit_Data_DMA(uint8_t *data, uint16_t size)
{
	uint8_t status = 0;

	spi_write_data_dma(data, size);

	return status;
}

uint8_t W25Q64_SPI_Receive_Data_DMA(uint8_t *data, uint16_t size)
{
	uint8_t status = 0;

	spi_read_data_dma(data, size);

	return status;
}

void W25Q64_Set_ChipSelect_Low(void)
{
	spi_cs_set_low();
}

void W25Q64_Set_ChipSelect_High(void)
{
	spi_cs_set_high();
}
