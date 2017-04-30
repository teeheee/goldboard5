/*
 * i2c.cpp
 *
 *  Created on: 23.04.2017
 *      Author: alex
 */

#include "i2c.h"

void UB_System_ClockEnable(GPIO_TypeDef* PORT)
{
  if(PORT==GPIOA) __GPIOA_CLK_ENABLE();
  if(PORT==GPIOB) __GPIOB_CLK_ENABLE();
  if(PORT==GPIOC) __GPIOC_CLK_ENABLE();
  if(PORT==GPIOD) __GPIOD_CLK_ENABLE();
  if(PORT==GPIOE) __GPIOE_CLK_ENABLE();
  if(PORT==GPIOF) __GPIOF_CLK_ENABLE();
  if(PORT==GPIOG) __GPIOG_CLK_ENABLE();
  if(PORT==GPIOH) __GPIOH_CLK_ENABLE();
  if(PORT==GPIOI) __GPIOI_CLK_ENABLE();
  if(PORT==GPIOJ) __GPIOJ_CLK_ENABLE();
  if(PORT==GPIOK) __GPIOK_CLK_ENABLE();
}

i2c::i2c(uint8_t _i2c_nummer) {
	i2c_nummer = _i2c_nummer;
	i2cConfigure(_i2c_nummer);
	gpioConfigure(_i2c_nummer);
	clockConfigure(_i2c_nummer);
}

int i2c::writeByte(uint8_t addr, uint8_t data) {
	  int ret_wert=0;
	  // adresse und wert senden
	  if(HAL_I2C_Master_Transmit(&i2c_handle, (uint8_t)addr, (uint8_t*)&data, 1, 20)!= HAL_OK)
	  {
	    ret_wert=-1;
	    if (HAL_I2C_GetError(&i2c_handle) != HAL_I2C_ERROR_AF)
	    	ret_wert=-2;
	  }
	  return ret_wert;
}

void i2c::gpioConfigure(uint8_t i2c_nummer) {

	scl_initdef.Mode = GPIO_MODE_AF_OD;
	scl_initdef.Pull = GPIO_PULLUP;
	scl_initdef.Speed = GPIO_SPEED_HIGH;
	sda_initdef.Mode = GPIO_MODE_AF_OD;
	sda_initdef.Pull = GPIO_PULLUP;
	sda_initdef.Speed = GPIO_SPEED_HIGH;

	if(i2c_nummer==I2C_1)
	{
		sda_initdef.Pin = I2C1_SDA_PIN;
		sda_initdef.Alternate = GPIO_AF4_I2C1;
		scl_initdef.Pin = I2C1_SCL_PIN;
		scl_initdef.Alternate = GPIO_AF4_I2C1;
	    HAL_GPIO_Init(I2C1_SCL_PORT, &scl_initdef);
	    HAL_GPIO_Init(I2C1_SDA_PORT, &sda_initdef);
	    UB_System_ClockEnable(I2C1_SCL_PORT);
		UB_System_ClockEnable(I2C1_SDA_PORT);
	}
}

void i2c::i2cConfigure(uint8_t i2c_nummer) {

	__HAL_RCC_I2C1_CLK_ENABLE();
	i2c_handle.Instance = I2C1;
	i2c_handle.Init.Timing = 0x40912732; // 100kHz
	i2c_handle.Init.OwnAddress1 = 0;
	i2c_handle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	i2c_handle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	i2c_handle.Init.OwnAddress2 = 0;
	i2c_handle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	i2c_handle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	HAL_I2C_Init(&i2c_handle);
}

void i2c::clockConfigure(uint8_t i2c_nummer) {
	RCC_PeriphCLKInitTypeDef RCC_PeriphCLKInitStruct;
	RCC_PeriphCLKInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
	RCC_PeriphCLKInitStruct.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
	HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphCLKInitStruct);


}
