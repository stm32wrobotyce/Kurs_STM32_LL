/*
 * spi.h
 *
 *  Created on: 12 sty 2023
 *      Author: piotr
 */

#ifndef SPI_H_
#define SPI_H_

#include "main.h"

void spi_init(void);
void spi_write_data(uint8_t *data, uint32_t size);
void spi_read_data(uint8_t *data, uint32_t size);

#endif /* SPI_H_ */
