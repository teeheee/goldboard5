/*
 * Display.h
 *
 *  Created on: 02.05.2017
 *      Author: alex
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "stm32f7xx.h"
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_lcd.h"

#define BUFFER_SIZE 255
#define LINES_SIZE  10

class Display {
public:
	Display();
	void printf(const char * format, ... );
private:
	void init();
	char* lines[LINES_SIZE];
	char buffer[BUFFER_SIZE];
	int write_position;
};

#endif /* DISPLAY_H_ */
