/*
 * goldboard5.h
 *
 *  Created on: 23.04.2017
 *      Author: alex
 */

#ifndef GOLDBOARD5_H_
#define GOLDBOARD5_H_


#include "stm32f7xx.h"
#include "stm32746g_discovery.h"

#include "stm32746g_discovery_lcd.h"
#include "i2c.h"
#include "PCF8574A.h"
#include "Motor.h"




class goldboard5{
private:
	i2c   i2cbus;
	PCF8574A pcf8564A;
public:
	Motor motors[4];
	goldboard5();
	void setLed(bool state);
	void delay(unsigned long time);
};


#endif /* GOLDBOARD5_H_ */
