/*
 * serial.h
 *
 *  Created on: 02.05.2017
 *      Author: alex
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#include "stm32f7xx_hal_uart.h"

class serial {
private:
	UART_HandleTypeDef uart_handle;
public:
	serial();
	void init(USART_TypeDef* Port,int baudrate);
	uint8_t getChar();
	void sendChar(uint8_t value);
	void getString(uint8_t* buffer,int buffer_size,uint8_t end_of_string);
	void sendString(uint8_t* buffer,int buffer_size);
};

#endif /* SERIAL_H_ */
