/*
 * i2c.h
 *
 *  Created on: 30 lis 2022
 *      Author: piotr
 */

#ifndef I2C_H_
#define I2C_H_

#include "main.h"

int32_t i2c_init(void);
int32_t i2c_write(uint16_t slave_addr, uint8_t *data_ptr, uint16_t size);
int32_t i2c_read(uint16_t slave_addr, uint8_t *data_ptr, uint16_t size);
int32_t i2c_reg_write(uint16_t slave_addr, uint16_t reg_addr, uint8_t *data_ptr, uint16_t size);
int32_t i2c_reg_read(uint16_t slave_addr, uint16_t reg_addr, uint8_t *read_data_ptr, uint16_t read_size);

#endif /* I2C_H_ */
