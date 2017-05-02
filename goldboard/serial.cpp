/*
 * serial.cpp
 *
 *  Created on: 02.05.2017
 *      Author: alex
 */

#include <serial.h>

serial::serial() {
}

void serial::init(USART_TypeDef* Port, int baudrate) {
	__GPIOA_CLK_ENABLE();
	__GPIOB_CLK_ENABLE();

	GPIO_InitTypeDef rx_initStruct;
	GPIO_InitTypeDef tx_initStruct;

	rx_initStruct.Pin = GPIO_PIN_9;
	rx_initStruct.Mode = GPIO_MODE_AF_PP;
	rx_initStruct.Pull = GPIO_PULLUP;
	rx_initStruct.Speed = GPIO_SPEED_HIGH;
	rx_initStruct.Alternate = GPIO_AF7_USART1;

	HAL_GPIO_Init(GPIOA, &rx_initStruct);

	tx_initStruct.Pin = GPIO_PIN_7;
	tx_initStruct.Mode = GPIO_MODE_AF_PP;
	tx_initStruct.Pull = GPIO_PULLUP;
	tx_initStruct.Speed = GPIO_SPEED_HIGH;
	tx_initStruct.Alternate = GPIO_AF7_USART1;

	HAL_GPIO_Init(GPIOB, &rx_initStruct);

	__USART1_CLK_ENABLE();

	uart_handle.Instance = Port;
	uart_handle.Init.BaudRate = baudrate;
	uart_handle.Init.WordLength = UART_WORDLENGTH_8B;
	uart_handle.Init.StopBits = UART_STOPBITS_1;
	uart_handle.Init.Parity = UART_PARITY_NONE;
	uart_handle.Init.Mode = UART_MODE_TX_RX;
	uart_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uart_handle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	HAL_UART_Init(&uart_handle);
}

uint8_t serial::getChar() {
	uint8_t data;
	HAL_UART_Receive(&uart_handle,&data,1,20);
	return data;
}


void serial::sendChar(uint8_t value)
{
	HAL_UART_Transmit(&uart_handle,&value,1,20);
}

