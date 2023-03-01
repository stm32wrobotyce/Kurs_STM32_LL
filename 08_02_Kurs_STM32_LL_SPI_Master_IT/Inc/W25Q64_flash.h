/*
 * W25Q64_Flash.h
 *
 *  Created on: Oct 28, 2021
 *      Author: piotr
 */

#ifndef INC_W25Q64_FLASH_H_
#define INC_W25Q64_FLASH_H_

#include "main.h"

#define PAGE_SIZE					256
#define SECTOR_SIZE					4096

struct memory_info
{
	uint8_t manufacturer_ID;
	uint8_t memory_type;
	uint8_t capacity;
};

uint8_t W25Q64_Init(void);

void W25Q64_ResetFlash(void);

void W25Q64_WriteEnable(void);
void W25Q64_WriteDisable(void);

uint8_t W25Q64_ReadStatusRegister1(void);
uint8_t W25Q64_ReadStatusRegister2(void);
void W25Q64_WriteStatusRegister(uint8_t, uint8_t);

uint8_t W25Q64_SectorErase(uint16_t);
uint8_t W25Q64_ChipErase(void);

uint8_t W25Q64_PageProgram(uint32_t, uint8_t *, uint16_t);
uint8_t W25Q64_ReadDataBytes(uint32_t adress, uint8_t *data, uint16_t size);

void W25Q64_get_JEDEC_ID(struct memory_info *info);

void W25Q64_WriteEnable_and_WaitForWriteEnableLatch(void);
void W25Q64_WaitForWriteEnableLatch(void);
void W25Q64_WaitForWriteInProgressClear(void);

uint8_t W25Q64_SPI_Transmit_Data(uint8_t *data, uint16_t size);
uint8_t W25Q64_SPI_Receive_Data(uint8_t *data, uint16_t size);
uint8_t W25Q64_SPI_Transmit_Data_IT(uint8_t *data, uint16_t size);
uint8_t W25Q64_SPI_Receive_Data_IT(uint8_t *data, uint16_t size);
void W25Q64_Set_ChipSelect_Low(void);
void W25Q64_Set_ChipSelect_High(void);

#endif /* INC_W25Q64_FLASH_H_ */
