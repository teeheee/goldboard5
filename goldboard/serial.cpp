/*
 * serial.cpp
 *
 *  Created on: 02.05.2017
 *      Author: alex
 */

#include "serial.h"

serial::serial() {
}

void serial::init(int uart_nummer, int baudrate) {

	GPIO_InitTypeDef rx_initStruct;
	GPIO_InitTypeDef tx_initStruct;
	rx_initStruct.Mode = GPIO_MODE_AF_PP;
	rx_initStruct.Pull = GPIO_PULLUP;
	rx_initStruct.Speed = GPIO_SPEED_HIGH;
	tx_initStruct.Mode = GPIO_MODE_AF_PP;
	tx_initStruct.Pull = GPIO_PULLUP;
	tx_initStruct.Speed = GPIO_SPEED_HIGH;

	if(uart_nummer==1)
	{
		UART1_TX_CLOCK();
		UART1_RX_CLOCK();
		rx_initStruct.Pin = UART1_RX_PIN;
		rx_initStruct.Alternate = UART1_AF;
		tx_initStruct.Pin = UART1_TX_PIN;
		tx_initStruct.Alternate = UART1_AF;
		HAL_GPIO_Init(UART1_RX_PORT, &rx_initStruct);
		HAL_GPIO_Init(UART1_TX_PORT, &tx_initStruct);
		UART1_CLOCK();
		uart_handle.Instance = UART1_INSTANCE;
	}
	else if(uart_nummer==6)
	{
		UART6_TX_CLOCK();
		UART6_RX_CLOCK();
		rx_initStruct.Pin = UART6_RX_PIN;
		rx_initStruct.Alternate = UART6_AF;
		tx_initStruct.Pin = UART6_TX_PIN;
		tx_initStruct.Alternate = UART6_AF;
		HAL_GPIO_Init(UART6_RX_PORT, &rx_initStruct);
		HAL_GPIO_Init(UART6_TX_PORT, &tx_initStruct);
		UART6_CLOCK();
		uart_handle.Instance = UART6_INSTANCE;
	}


	uart_handle.Init.BaudRate = baudrate;
	uart_handle.Init.WordLength = UART_WORDLENGTH_8B;
	uart_handle.Init.StopBits = UART_STOPBITS_1;
	uart_handle.Init.Parity = UART_PARITY_NONE;
	uart_handle.Init.Mode = UART_MODE_TX_RX;
	uart_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
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


void serial::getString(uint8_t* buffer,int buffer_size)
{
	HAL_UART_Transmit(&uart_handle,buffer,buffer_size,20);
}

void serial::sendString(uint8_t* buffer,int buffer_size)
{
	HAL_UART_Transmit(&uart_handle,buffer,buffer_size,20);
}

