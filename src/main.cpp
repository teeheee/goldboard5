#include "goldboard5.h"

goldboard5 gb;

int main(void) {
	gb.setLed(true); // this is a test comment from teeheee

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_PIN_8;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	// GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_9;
	// GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	__HAL_RCC_GPIOB_CLK_ENABLE()
	;

	while (1) {
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_8);
		gb.delay(10);
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_9);
		gb.delay(10);
	}
	for (;;)
		;
}
