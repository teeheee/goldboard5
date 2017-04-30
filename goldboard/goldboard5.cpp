/*
 * goldboard5.cpp
 *
 *  Created on: 23.04.2017
 *      Author: alex
 */


#include "goldboard5.h"


goldboard5::goldboard5()
{
	SystemInit();
	SystemCoreClockUpdate();
	HAL_Init();
	BSP_LED_Init(LED1);
}


void goldboard5::setLed(bool state)
{
	if(state)
		BSP_LED_On(LED1);
	else
		BSP_LED_Off(LED1);
}

void goldboard5::delay(unsigned long time)
{
	HAL_Delay(time);
}
