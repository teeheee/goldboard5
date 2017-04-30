/**********************************************************************
@file       Motor.cpp

@brief      Driver for motors on Goldboard4

-----------------------------------------------------------------------
@author  2015 Christoph Rothermel
         Christoph.Rothermel@gmx.de
-----------------------------------------------------------------------
@History

1.00 28.01.2015 First working version

@end
***********************************************************************/

#include "Motor.h"
#include <cstdlib>

Motor::Motor()
{
	
}

/*Motor::Motor(uint8_t directionPinFirst, uint8_t directionPinSecond, uint8_t speedPin)
{
	init(directionPinFirst, directionPinSecond, speedPin);
}*/

void Motor::init(uint8_t directionPinFirst, uint8_t directionPinSecond, uint32_t spPin,GPIO_TypeDef* spPort , PCF8574A* pcf8574)
{
	// private
	_directionPinFirst = directionPinFirst;
	_directionPinSecond = directionPinSecond;
	_pcf8574 = pcf8574;
	_spPin=spPin;
	_spPort=spPort;
	
	// public
	speed = 0;

	// set pin modes
	// NOTE: DIRECTION PINS are on PCF5784
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin  = spPin;			//GPIO_PIN_11
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(spPort, &GPIO_InitStruct);

	
	// set as leerlauf
	stop(false);	
}

void Motor::rotate(int16_t sp)
{
	if (sp == 0)
	{
		stop(false);
		HAL_GPIO_WritePin(_spPort, _spPin, GPIO_PIN_RESET);
		return;
	}
	else if(sp > 0)
	{
		_pcf8574->setPin(_directionPinFirst, LOW);
		_pcf8574->setPin(_directionPinSecond, HIGH);
		HAL_GPIO_WritePin(_spPort, _spPin, GPIO_PIN_SET);
	}
	else
	{
		_pcf8574->setPin(_directionPinFirst, HIGH);
		_pcf8574->setPin(_directionPinSecond, LOW);
		HAL_GPIO_WritePin(_spPort, _spPin, GPIO_PIN_SET);
	}
	_pcf8574->write();
	
	// Offset beachten!
	sp = abs(sp);
	if (sp > 255)
		sp = 255;
		
	
	speed = (uint8_t) sp;
}

void Motor::stop(bool bremsen)
{
	if(bremsen) // motor bremsen (sollte nur im notfall verwendet werden)
	{	
		speed = 255;
		_pcf8574->setPin(_directionPinFirst, HIGH);
		_pcf8574->setPin(_directionPinSecond, HIGH);
	}
	else // motor auslaufen lassen
	{
		speed = 0;
		_pcf8574->setPin(_directionPinFirst, LOW);
		_pcf8574->setPin(_directionPinSecond, LOW);
	}
	_pcf8574->write();
}
