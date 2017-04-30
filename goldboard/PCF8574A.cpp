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


#ifdef __cplusplus
extern "C" {
#endif
	#include "stm32_ub_i2c1.h"
#ifdef __cplusplus
}
#endif


#define PCF8574A_ADDRESS 0b01110000 


// default constructor
PCF8574A::PCF8574A()
{
	_pcfdata = 0;
	_writeNeeded = true;
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
	UB_I2C1_ReadByte(PCF8574A_ADDRESS ,_pcfdata);
	return _pcfdata;
}

void PCF8574A::write()
{
	// only write if it's really needed, i2c writing costs time...
	if (!_writeNeeded)
		return;

	UB_I2C1_WriteCMD((uint8_t)PCF8574A_ADDRESS,_pcfdata);
	//i2cWriteToSlave (PCF8574A_ADDRESS, &_pcfdata, 1);
	_writeNeeded = false;
}
