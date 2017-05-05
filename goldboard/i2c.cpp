/*
 * i2c.cpp
 *
 *  Created on: 23.04.2017
 *      Author: alex
 */

#include "i2c.h"

i2c::i2c() {

}

void i2c::init(uint8_t _i2c_nummer)
{
	i2c_nummer = _i2c_nummer;
	if(i2c_nummer==I2C_1)
	{
		i2cConfigure(_i2c_nummer);
		gpioConfigure(_i2c_nummer);
	}
	else if(i2c_nummer==I2C_3)
	{
		i2cConfigure(_i2c_nummer);
		gpioConfigure(_i2c_nummer);
	}
}

void i2c::writeByte(uint8_t addr, uint8_t data) {

	  // adresse und wert senden
	  if(HAL_I2C_Master_Transmit(&i2c_handle, (uint8_t)addr, (uint8_t*)&data, 1, 20)!= HAL_OK)
	  {
	    if (HAL_I2C_GetError(&i2c_handle) != HAL_I2C_ERROR_AF)
	    {
	    	return;
	    }
	  }
}

uint8_t i2c::readByte(uint8_t addr)
{
	uint8_t data;
	if(HAL_I2C_Master_Receive(&i2c_handle, (uint8_t)addr, (uint8_t*)&data, 1, 20)!= HAL_OK)
	{
		    if (HAL_I2C_GetError(&i2c_handle) != HAL_I2C_ERROR_AF)
		    {
		    	return 0;
		    }
		    return 0;
	}
	return data;
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
		__GPIOB_CLK_ENABLE(); //muss vor HAL_GPIO_Init kommen
	    HAL_GPIO_Init(I2C1_SCL_PORT, &scl_initdef);
	    HAL_GPIO_Init(I2C1_SDA_PORT, &sda_initdef);
	}
	else if(i2c_nummer==I2C_3)
	{

		sda_initdef.Pin = I2C3_SDA_PIN;
		sda_initdef.Alternate = GPIO_AF4_I2C3;
		scl_initdef.Pin = I2C3_SCL_PIN;
		scl_initdef.Alternate = GPIO_AF4_I2C3;
		__GPIOH_CLK_ENABLE(); //muss vor HAL_GPIO_Init kommen
	    HAL_GPIO_Init(I2C3_SCL_PORT, &scl_initdef);
	    HAL_GPIO_Init(I2C3_SDA_PORT, &sda_initdef);
	}
			return;
}

void i2c::i2cConfigure(uint8_t i2c_nummer) {

	if(i2c_nummer==I2C_1)
	{
		__HAL_RCC_I2C1_CLK_ENABLE();//muss vor HAL_I2C_Init kommen
		i2c_handle.Instance = I2C1;
	}
	else if(i2c_nummer==I2C_3)
	{
		__HAL_RCC_I2C3_CLK_ENABLE();//muss vor HAL_I2C_Init kommen
		i2c_handle.Instance = I2C3;
	}
	else
		return;
	i2c_handle.Init.Timing = 0x40912732; // 100kHz
	i2c_handle.Init.OwnAddress1 = 0;
	i2c_handle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	i2c_handle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	i2c_handle.Init.OwnAddress2 = 0;
	i2c_handle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	i2c_handle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	HAL_I2C_Init(&i2c_handle);
}

//--------------------------------------------------------------
// Auslesen einer Adresse per I2C von einem Slave
// slave_adr => I2C-Basis-Adresse vom Slave
// adr       => Register Adresse die gelesen wird
//
// Return_wert :
//  0...255 , Bytewert der gelesen wurde
//  < 0     , Error
//--------------------------------------------------------------
int16_t i2c::I2C_ReadByte(uint8_t slave_adr, uint8_t adr)
{
  int16_t ret_wert=0;

  I2C3_DATA[0]=adr;

  // adresse senden
  if(HAL_I2C_Master_Transmit(&i2c_handle, (uint16_t)slave_adr, (uint8_t*)I2C3_DATA, 1, I2C3_TIMEOUT)!= HAL_OK)
  {
    ret_wert=-1;
    if (HAL_I2C_GetError(&i2c_handle) != HAL_I2C_ERROR_AF) ret_wert=-2;
  }
  if(ret_wert!=0) return(ret_wert);

  // daten lesen
  if(HAL_I2C_Master_Receive(&i2c_handle, (uint16_t)slave_adr, (uint8_t *)I2C3_DATA, 1, I2C3_TIMEOUT) != HAL_OK)
  {
    ret_wert=-3;
    if (HAL_I2C_GetError(&i2c_handle) != HAL_I2C_ERROR_AF) ret_wert=-4;
  }
  if(ret_wert!=0) return(ret_wert);

  // daten
  ret_wert=I2C3_DATA[0];

  return(ret_wert);
}


//--------------------------------------------------------------
// Beschreiben einer Adresse per I2C von einem Slave
// slave_adr => I2C-Basis-Adresse vom Slave
// adr       => Register Adresse die beschrieben wird
// wert      => Bytewert der geschrieben wird
//
// Return_wert :
//    0   , Ok
//  < 0   , Error
//--------------------------------------------------------------
int16_t i2c::I2C_WriteByte(uint8_t slave_adr, uint8_t adr, uint8_t wert)
{
  int16_t ret_wert=0;

  I2C3_DATA[0]=adr;
  I2C3_DATA[1]=wert;

  // adresse und wert senden
  if(HAL_I2C_Master_Transmit(&i2c_handle, (uint16_t)slave_adr, (uint8_t*)I2C3_DATA, 2, I2C3_TIMEOUT)!= HAL_OK)
  {
    ret_wert=-1;
    if (HAL_I2C_GetError(&i2c_handle) != HAL_I2C_ERROR_AF) ret_wert=-2;
  }

  return(ret_wert);
}



//--------------------------------------------------------------
// Auslesen mehrerer Adresse per I2C von einem Slave
// slave_adr => I2C-Basis-Adresse vom Slave
// adr       => Start Register Adresse ab der gelesen wird
// cnt       => Anzahl der Bytewert die gelesen werden sollen
// Daten die gelesen worden sind, stehen danach in "I2C3_DATA"
//
// Return_wert :
//    0   , Ok
//  < 0   , Error
//--------------------------------------------------------------
int16_t i2c::I2C_ReadMultiByte(uint8_t slave_adr, uint8_t adr, uint8_t cnt)
{
  int16_t ret_wert=0;

  I2C3_DATA[0]=adr;

  // adresse senden
  if(HAL_I2C_Master_Transmit(&i2c_handle, (uint16_t)slave_adr, (uint8_t*)I2C3_DATA, 1, I2C3_TIMEOUT)!= HAL_OK)
  {
    ret_wert=-1;
    if (HAL_I2C_GetError(&i2c_handle) != HAL_I2C_ERROR_AF) ret_wert=-2;
  }
  if(ret_wert!=0) return(ret_wert);

  // daten lesen
  if(HAL_I2C_Master_Receive(&i2c_handle, (uint16_t)slave_adr, (uint8_t *)I2C3_DATA, cnt, I2C3_TIMEOUT) != HAL_OK)
  {
    ret_wert=-3;
    if (HAL_I2C_GetError(&i2c_handle) != HAL_I2C_ERROR_AF) ret_wert=-4;
  }
  if(ret_wert!=0) return(ret_wert);

  return(ret_wert);
}

//--------------------------------------------------------------
// Beschreiben mehrerer Adresse per I2C von einem Slave
// slave_adr => I2C-Basis-Adresse vom Slave
// adr       => Start Register Adresse ab der beschrieben wird
// cnt       => Anzahl der Bytewert die geschrieben werden sollen
// Daten die geschrieben werden sollen, müssen in "I2C3_DATA" stehen
//
// Return_wert :
//    0   , Ok
//  < 0   , Error
//--------------------------------------------------------------
int16_t i2c::I2C_WriteMultiByte(uint8_t slave_adr, uint8_t adr, uint8_t cnt)
{
  int16_t ret_wert=0;
  uint16_t n;

  for(n=cnt;n>0;n--) {
    I2C3_DATA[n]=I2C3_DATA[n-1];
  }
  I2C3_DATA[0]=adr;

  // adresse und alle daten senden
  if(HAL_I2C_Master_Transmit(&i2c_handle, (uint16_t)slave_adr, (uint8_t*)I2C3_DATA, cnt+1, I2C3_TIMEOUT)!= HAL_OK)
  {
    ret_wert=-1;
    if (HAL_I2C_GetError(&i2c_handle) != HAL_I2C_ERROR_AF) ret_wert=-2;
  }

  return(ret_wert);
}

