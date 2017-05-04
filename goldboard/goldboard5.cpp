/*
 * goldboard5.cpp
 *
 *  Created on: 23.04.2017
 *      Author: alex
 */

#include "goldboard5.h"


//void goldboard::SystemClock_Config() {
//	RCC_ClkInitTypeDef RCC_ClkInitStruct;
//	RCC_OscInitTypeDef RCC_OscInitStruct;
//	HAL_StatusTypeDef ret = HAL_OK;
//
//	/* Enable HSE Oscillator and activate PLL with HSE as source*/
//	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
//	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
//	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
//	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
//	RCC_OscInitStruct.PLL.PLLM = 25;
//	RCC_OscInitStruct.PLL.PLLN = 400;
//	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
//	RCC_OscInitStruct.PLL.PLLQ = 8;
//
//	ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
//	if (ret != HAL_OK) {
//		while (1) {
//			;
//		}
//	}
//
//	/* Activate the OverDrive to reach the 200 MHz Frequency
//	 ret = HAL_PWREx_EnableOverDrive();
//	 if(ret != HAL_OK)
//	 {
//	 while(1) { ; }
//	 }*/
//
//	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers*/
//	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK
//			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
//	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
//	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
//	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
//	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
//
//	ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_6);
//	if (ret != HAL_OK) {
//		while (1) {
//			;
//		}
//	}
//}

goldboard5::goldboard5() {
	HAL_Init();
	SystemClock_Config();
	BSP_LED_Init(LED1);

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOI_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();

	i2cbus.init(I2C_1);
	pcf8564A.init(&i2cbus);

	motors[0].init(0, 1, GPIO_PIN_8, GPIOA, &pcf8564A);
	motors[1].init(2, 3, GPIO_PIN_6, GPIOG, &pcf8564A);
	motors[2].init(4, 5, GPIO_PIN_4, GPIOB, &pcf8564A);
	motors[3].init(6, 7, GPIO_PIN_7, GPIOG, &pcf8564A);


}

void goldboard5::setLed(bool state) {
	if (state)
		BSP_LED_On(LED1);
	else
		BSP_LED_Off(LED1);
}

void goldboard5::delay(unsigned long time) {
	HAL_Delay(time);
}

