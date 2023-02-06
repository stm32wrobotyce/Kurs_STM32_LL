/*
 * i2c.h
 *
 *  Created on: 30 lis 2022
 *      Author: piotr
 */

#ifndef I2C_H_
#define I2C_H_

#include "main.h"

typedef struct
{
	uint8_t* data_ptr;
	uint32_t count;
}buffer_t;

int32_t i2c_init(void);
int32_t i2c_reg_write_it(uint16_t slave_addr, uint16_t reg_addr, uint8_t *data_ptr, uint16_t size);
int32_t i2c_reg_read_it(uint16_t slave_addr, uint16_t reg_addr, uint8_t *data_ptr, uint16_t size);

void i2c_it_transmit_callback(void);
void i2c_it_receive_callback(void);

#endif /* I2C_H_ */
