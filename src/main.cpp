#include "goldboard5.h"
//#include "i2c.h"
#include <stdlib.h>
#include "stm32746g_discovery_lcd.h"

int linecounter = 0;

void displaystatus(HAL_StatusTypeDef ret) {
	if (ret == HAL_OK)
		BSP_LCD_DisplayStringAtLine(linecounter++, (uint8_t*) "HAL_OK");
	if (ret == HAL_ERROR)
		BSP_LCD_DisplayStringAtLine(linecounter++, (uint8_t*) "HAL_ERROR");
	if (ret == HAL_BUSY)
		BSP_LCD_DisplayStringAtLine(linecounter++, (uint8_t*) "HAL_BUSY");
	if (ret == HAL_TIMEOUT)
		BSP_LCD_DisplayStringAtLine(linecounter++, (uint8_t*) "HAL_TIMEOUT");
}




int main(void) {

	goldboard5 gb;
	BSP_LCD_DisplayStringAtLine(linecounter++, (uint8_t*) "start2");


	HAL_StatusTypeDef ret;

	//1.Declare a I2C_HandleTypeDef handle structure, for example: I2C_HandleTypeDef hi2c;
	I2C_HandleTypeDef i2c_handle;
    //a. Enable the I2Cx interface clock
	__HAL_RCC_I2C1_CLK_ENABLE();

	//I2C pins configuration
	//Enable the clock for the I2C GPIOs
	__GPIOB_CLK_ENABLE();
	//Configure I2C pins as alternate function open-drain
	GPIO_InitTypeDef scl_initdef;
	scl_initdef.Mode = GPIO_MODE_AF_OD;
	scl_initdef.Pull = GPIO_PULLUP;
	scl_initdef.Speed = GPIO_SPEED_HIGH;
	scl_initdef.Pin = GPIO_PIN_8;
	scl_initdef.Alternate = GPIO_AF4_I2C1;
	HAL_GPIO_Init(GPIOB, &scl_initdef);


	GPIO_InitTypeDef sda_initdef;
	sda_initdef.Mode = GPIO_MODE_AF_OD;
	sda_initdef.Pull = GPIO_PULLUP;
	sda_initdef.Speed = GPIO_SPEED_HIGH;
	sda_initdef.Pin = GPIO_PIN_9;
	sda_initdef.Alternate = GPIO_AF4_I2C1;
	HAL_GPIO_Init(GPIOB, &sda_initdef);


	BSP_LCD_DisplayStringAtLine(linecounter++, (uint8_t*) "gpio configured");
    //NVIC configuration if you need to use interrupt process
    //DMA Configuration if you need to use DMA process

	//Configure the Communication Clock Timing, Own Address1, Master Addressing
	//mode, Dual Addressing mode, Own Address2, Own Address2 Mask, General call and
	//Nostretch mode in the hi2c Init structure. i2c_handle.Instance = I2C1;
	i2c_handle.Init.Timing = 0x40912732; // 100kHz
	i2c_handle.Init.OwnAddress1 = 0;
	i2c_handle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	i2c_handle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	i2c_handle.Init.OwnAddress2 = 0;
	i2c_handle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	i2c_handle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	//4.Initialize the I2C registers by calling the HAL_I2C_Init(), configures also the low level
	//Hardware (GPIO, CLOCK, NVIC...etc) by calling the customized  HAL_I2C_MspInit(&hi2c) API.
	ret = HAL_I2C_Init(&i2c_handle);
	displaystatus(ret);

	RCC_PeriphCLKInitTypeDef RCC_PeriphCLKInitStruct;
	RCC_PeriphCLKInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
	RCC_PeriphCLKInitStruct.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
	ret = HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphCLKInitStruct);
	displaystatus(ret);


	//To check if target device is ready for communication, use the function HAL_I2C_IsDeviceReady()
	ret = HAL_I2C_IsDeviceReady(&i2c_handle,0x42,5,2);
	displaystatus(ret);


	BSP_LCD_DisplayStringAtLine(linecounter++, (uint8_t*) "i2c configured");


	/**/

	uint8_t data = 2;
	ret = HAL_I2C_Master_Transmit(&i2c_handle, 0x42, (uint8_t*) &data, 1, 20);
	displaystatus(ret);

	uint32_t error = HAL_I2C_GetError(&i2c_handle);
	HAL_I2C_StateTypeDef state = HAL_I2C_GetState(&i2c_handle);
	HAL_I2C_ModeTypeDef mode = HAL_I2C_GetMode(&i2c_handle);

	char buffer[100];
	itoa(error, buffer, 16);
	BSP_LCD_DisplayStringAtLine(linecounter++, (uint8_t*) buffer);
	itoa(state, buffer, 16);
	BSP_LCD_DisplayStringAtLine(linecounter++, (uint8_t*) buffer);
	itoa(mode, buffer, 16);
	BSP_LCD_DisplayStringAtLine(linecounter++, (uint8_t*) buffer);

	while (1) {
		uint8_t data = 2;
		HAL_I2C_Master_Transmit(&i2c_handle, 0x42, (uint8_t*) &data, 1, 20);

		gb.setLed(true);
		gb.delay(100);
		gb.setLed(false);
		gb.delay(100);
	}
}
