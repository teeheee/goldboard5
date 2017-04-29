/**********************************************************************
@file       Motor.h

@brief      Driver for motors on Goldboard4

-----------------------------------------------------------------------
@author  2015 Christoph Rothermel
         Christoph.Rothermel@gmx.de
-----------------------------------------------------------------------
@History

1.00 28.01.2015 First working version

@end
***********************************************************************/

#ifndef MOTOR_H_
#define MOTOR_h_

#define LOW 0
#define HIGH 1

#include "PCF8574A.h"

class Motor
{
	public:
		Motor();
		//Motor(uint8_t directionPinFirst, uint8_t directionPinSecond, uint8_t speedPin);
		void init(uint8_t directionPinFirst, uint8_t directionPinSecond, uint8_t spPin, PCF8574A* pcf8574, uint8_t* gbSpeed);
		void rotate(int16_t sp);
		void stop(bool bremsen);
		
		uint8_t* speed;
	private:
		PCF8574A* _pcf8574;
		uint8_t _directionPinFirst;
		uint8_t _directionPinSecond;
};
#endif
