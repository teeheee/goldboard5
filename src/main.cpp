#include "goldboard5.h"
#include "i2c.h"

int main(void) {

	goldboard5 gb;
	i2c data(I2C_1);
	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_GPIOG_CLK_ENABLE();

	GPIO_InitStruct.Pin = GPIO_PIN_6;			//GPIO_PIN_11
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_SET);
	while(1)
	{
		data.writeByte(0x41,1<<6);
		gb.delay(1000);
		data.writeByte(0x41,1<<7);
		gb.delay(1000);
		data.writeByte(0x41,0);
		gb.delay(1000);
	}
}
