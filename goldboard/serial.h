/*
 * serial.h
 *
 *  Created on: 02.05.2017
 *      Author: alex
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#include "stm32f7xx.h"
#include "stm32746g_discovery.h"
#include "stm32f7xx_hal_usart.h"

/***uart1****/
#define UART1_TX_PORT		GPIOB
#define UART1_TX_PIN		GPIO_PIN_7
#define UART1_TX_CLOCK()	__GPIOB_CLK_ENABLE()
#define UART1_RX_PORT		GPIOA
#define UART1_RX_PIN		GPIO_PIN_9
#define UART1_RX_CLOCK()	__GPIOA_CLK_ENABLE()
#define UART1_INSTANCE		USART1
#define UART1_AF			GPIO_AF7_USART1
#define UART1_CLOCK() 		__USART1_CLK_ENABLE()

/***uart6****/
#define UART6_TX_PORT		GPIOC
#define UART6_TX_PIN		GPIO_PIN_6
#define UART6_TX_CLOCK()	__GPIOC_CLK_ENABLE()
#define UART6_RX_PORT		GPIOC
#define UART6_RX_PIN		GPIO_PIN_7
#define UART6_RX_CLOCK()	__GPIOC_CLK_ENABLE()
#define UART6_INSTANCE		USART6
#define UART6_AF			GPIO_AF8_USART6
#define UART6_CLOCK() 		__USART6_CLK_ENABLE()


class serial {
private:
	USART_HandleTypeDef uart_handle;
public:
	serial();
	void init(int uart_nummer,int baudrate);
	uint8_t getChar();
	void sendChar(uint8_t value);
	void getString(uint8_t* buffer,int buffer_size,uint8_t end_of_string);
	void sendString(uint8_t* buffer,int buffer_size);
};

#endif /* SERIAL_H_ */
