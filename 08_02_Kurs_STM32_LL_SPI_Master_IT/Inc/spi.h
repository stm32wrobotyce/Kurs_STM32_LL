/*
 * spi.h
 *
 *  Created on: 12 sty 2023
 *      Author: piotr
 */

#ifndef SPI_H_
#define SPI_H_

#include "spi.h"
#include "main.h"

typedef struct
{
	uint8_t* data_ptr;
	uint32_t count;
}buffer_t;

typedef enum
{
	TRANSMIT = 0,
	RECEIVE = 1
}transfer_type_t;

void spi_init(void);

void spi_cs_set_high(void);
void spi_cs_set_low(void);

void spi_write_data(uint8_t *data, uint32_t size);
void spi_read_data(uint8_t *data, uint32_t size);

void spi_write_data_it(uint8_t *data, uint32_t size);
void spi_read_data_it(uint8_t *data, uint32_t size);

void spi_it_transmit_callback(void);
void spi_it_receive_callback(void);

void spi_transfer_cplt_callback(transfer_type_t type);

#endif /* SPI_H_ */
