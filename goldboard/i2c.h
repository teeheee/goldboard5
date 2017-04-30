/*
 * i2c.h
 *
 *  Created on: 23.04.2017
 *      Author: alex
 */

#ifndef I2C_H_
#define I2C_H_


#include "stm32f7xx.h"
#include "stm32746g_discovery.h"

#define I2C_1 1
#define I2C_2 2
#define I2C_3 3

#define I2C1_SCL_PORT GPIOB
#define I2C1_SCL_PIN  GPIO_PIN_8
#define I2C1_SDA_PORT GPIOB
#define I2C1_SDA_PIN  GPIO_PIN_9



class i2c{
public:
	i2c(uint8_t _i2c_nummer);
	void writeByte(uint8_t addr,uint8_t data);
	uint8_t readByte(uint8_t addr);
private:
	uint8_t i2c_nummer;
	GPIO_InitTypeDef scl_initdef;
	GPIO_InitTypeDef sda_initdef;
	I2C_HandleTypeDef i2c_handle;
	void i2cConfigure(uint8_t _i2c_nummer);
	void gpioConfigure(uint8_t _i2c_nummer);
};


#endif /* GOLDBOARD5_H_ */
