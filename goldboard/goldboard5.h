/*
 * goldboard5.h
 *
 *  Created on: 23.04.2017
 *      Author: alex
 */

#ifndef GOLDBOARD5_H_
#define GOLDBOARD5_H_


#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_lcd.h"
//#include "Motor.h"
#include <cstdlib>



class goldboard5{
public:
	goldboard5();
	void setLed(bool state);
	void DisplayPrintNum(uint16_t line, int16_t num);
	void DisplayPrintNumAt(uint16_t Xpos, uint16_t Ypos, int16_t num, Text_AlignModeTypdef Mode);
	void DisplayStringAtLine(uint16_t Line, uint8_t *ptr);
	void DisplayStringAt(uint16_t Xpos, uint16_t Ypos, uint8_t *Text, Text_AlignModeTypdef Mode);
	void DisplayConfig();
	void DisplayClearLine(uint32_t Line);
	void Delay(__IO uint32_t Delay);
	void DisplayClear();
	uint32_t millis();
	void DisplaySetTextColor(uint32_t Color);
	void ButtonInit(uint16_t PIN);
	uint8_t digitalgetValue(uint16_t GPIO_Pin);
	void LedInit(uint16_t PIN);
	void SystemClock_Config();
};


#endif /* GOLDBOARD5_H_ */
