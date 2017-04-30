/**********************************************************************
@file       PCF8574A.cpp

@brief      Driver for the PCF8574A Remote 8-Bit I/O expander

-----------------------------------------------------------------------
@author  2015 Christoph Rothermel
         Christoph.Rothermel@gmx.de
-----------------------------------------------------------------------
@History

1.00 28.01.2015 First working version

@end
***********************************************************************/

#include "PCF8574A.h"



#define PCF8574A_ADDRESS 0x41


// default constructor
PCF8574A::PCF8574A()
{
	_pcfdata = 0;
	_writeNeeded = true;
	_i2cBus=0;
}

void PCF8574A::init(i2c* i2cBus)
{
	_i2cBus = i2cBus;
}

void PCF8574A::setPin(uint8_t pin, bool val)
{
	uint8_t oldPCFData = _pcfdata;
	if (val)
		_pcfdata |= (1 << pin);
	else
		_pcfdata &= ~(1 << pin);
		
	if (oldPCFData != _pcfdata)
		_writeNeeded = true;
}

uint8_t PCF8574A::read()
{
	_pcfdata = _i2cBus->readByte(PCF8574A_ADDRESS);
	return _pcfdata;
}

void PCF8574A::write()
{
	// only write if it's really needed, i2c writing costs time...
	if (!_writeNeeded)
		return;

	_i2cBus->writeByte(PCF8574A_ADDRESS ,_pcfdata);
	_writeNeeded = false;
}
