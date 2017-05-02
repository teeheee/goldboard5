#include "goldboard5.h"



#include "stm32f7xx.h"
#include "stm32746g_discovery.h"
#include "stm32f7xx_hal_usart.h"

int main(void) {
	goldboard5 gb;
	USART_HandleTypeDef uart_handle;
	GPIO_InitTypeDef rx_initStruct;
	GPIO_InitTypeDef tx_initStruct;

	__GPIOC_CLK_ENABLE();
	tx_initStruct.Mode = GPIO_MODE_AF_PP;
	tx_initStruct.Pull = GPIO_PULLUP;
	tx_initStruct.Speed = GPIO_SPEED_HIGH;
	tx_initStruct.Pin = GPIO_PIN_6;
	tx_initStruct.Alternate = GPIO_AF8_USART6;
	HAL_GPIO_Init(GPIOC, &tx_initStruct);

	__GPIOC_CLK_ENABLE();
	rx_initStruct.Mode = GPIO_MODE_AF_OD;
	rx_initStruct.Pull = GPIO_PULLUP;
	rx_initStruct.Speed = GPIO_SPEED_HIGH;
	rx_initStruct.Pin = GPIO_PIN_7;
	rx_initStruct.Alternate = GPIO_AF8_USART6;
	HAL_GPIO_Init(GPIOC, &rx_initStruct);

	__USART6_CLK_ENABLE();
	uart_handle.Instance = USART6;
	uart_handle.Init.BaudRate = 9600;
	uart_handle.Init.WordLength = UART_WORDLENGTH_8B;
	uart_handle.Init.StopBits = UART_STOPBITS_1;
	uart_handle.Init.Parity = UART_PARITY_NONE;
	uart_handle.Init.Mode = UART_MODE_TX_RX;
	HAL_USART_Init(&uart_handle);
	while (1) {
		gb.delay(100);
		uint8_t value=10;
		HAL_USART_Transmit(&uart_handle, &value, 1, 20);
	}
}
