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



class goldboard5{
public:
	goldboard5();
	void setLed(bool state);
};


#endif /* GOLDBOARD5_H_ */
