//--------------------------------------------------------------
// File     : stm32_UB_I2C1.h
//--------------------------------------------------------------

//--------------------------------------------------------------
#ifndef __STM32F7_UB_I2C1_H
#define __STM32F7_UB_I2C1_H

//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
//#include "stm32_ub_system.h"
#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"


//--------------------------------------------------------------
// MultiByte defines
//--------------------------------------------------------------
#define    I2C1_MULTIBYTE_ANZ   10         // anzahl der Bytes




//--------------------------------------------------------------
// APB1-Clock = 50MHz
//--------------------------------------------------------------
#define I2C1_TIMING      0x40912732   // 100kHz



//--------------------------------------------------------------
// Defines
//-------------------------------------------------------------- 
#define   I2C1_TIMEOUT     1000       // Timeout Zeit in ms



//--------------------------------------------------------------
// I2C-GPIO-Pins
// moegliche Pinbelegung :
//   SCL : [PA8, PH7]
//   SDA : [PC9, PH8]
//--------------------------------------------------------------
#define  I2C1_SCL_PORT    GPIOB
#define  I2C1_SCL_PIN     GPIO_PIN_8

#define  I2C1_SDA_PORT    GPIOB
#define  I2C1_SDA_PIN     GPIO_PIN_9


//--------------------------------------------------------------
// Globale Funktionen
//--------------------------------------------------------------
void UB_I2C1_Init(void);
int16_t UB_I2C1_ReadByte(uint8_t slave_adr, uint8_t adr);
int16_t UB_I2C1_WriteByte(uint8_t slave_adr, uint8_t adr, uint8_t wert);
int16_t UB_I2C1_ReadMultiByte(uint8_t slave_adr, uint8_t adr, uint8_t cnt);
int16_t UB_I2C1_WriteMultiByte(uint8_t slave_adr, uint8_t adr, uint8_t cnt);
int16_t UB_I2C1_WriteCMD(uint8_t slave_adr, uint8_t cmd);
int16_t UB_I2C1_ReadByte16(uint8_t slave_adr, uint16_t adr);
int16_t UB_I2C1_WriteByte16(uint8_t slave_adr, uint16_t adr, uint8_t wert);
void UB_I2C1_Delay(volatile uint32_t nCount);




//--------------------------------------------------------------
#endif // __STM32F7_UB_I2C1_H
