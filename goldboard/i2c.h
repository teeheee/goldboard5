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

#define I2C3_SCL_PORT GPIOH
#define I2C3_SCL_PIN GPIO_PIN_7

#define I2C3_SDA_PORT GPIOH
#define I2C3_SDA_PIN GPIO_PIN_8

//--------------------------------------------------------------
// MultiByte defines
//--------------------------------------------------------------
#define    I2C3_MULTIBYTE_ANZ   10         // anzahl der Bytes
//--------------------------------------------------------------
// APB1-Clock = 50MHz
//--------------------------------------------------------------
#define I2C3_TIMING      0x40912732   // 100kHz

//--------------------------------------------------------------
// Defines
//--------------------------------------------------------------
#define   I2C3_TIMEOUT     1000       // Timeout Zeit in ms

class i2c{
public:
	i2c();
	void init(uint8_t _i2c_nummer);
	void writeByte(uint8_t addr,uint8_t data);
	uint8_t readByte(uint8_t addr);
	int16_t I2C_ReadByte(uint8_t slave_adr, uint8_t adr);
	int16_t I2C_WriteByte(uint8_t slave_adr, uint8_t adr, uint8_t wert);
	int16_t I2C_ReadMultiByte(uint8_t slave_adr, uint8_t adr, uint8_t cnt);
	int16_t I2C_WriteMultiByte(uint8_t slave_adr, uint8_t adr, uint8_t cnt);
private:
	static uint8_t I2C3_DATA[I2C3_MULTIBYTE_ANZ];  // Array
	uint8_t i2c_nummer;
	GPIO_InitTypeDef scl_initdef;
	GPIO_InitTypeDef sda_initdef;
	I2C_HandleTypeDef i2c_handle;
	void i2cConfigure(uint8_t _i2c_nummer);
	void gpioConfigure(uint8_t _i2c_nummer);
};


#endif /* GOLDBOARD5_H_ */
