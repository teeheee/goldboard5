/*
 * Display.cpp
 *
 *  Created on: 02.05.2017
 *      Author: alex
 */

#include <Display.h>

Display::Display() {
	init();
	for(int i = 0; i < BUFFER_SIZE;i++)
		buffer[i]=0;

	for(int i = 0; i < LINES_SIZE;i++)
		lines[i]=NULL;

	write_position = 0;
}


void Display::init() {
	/* LCD Initialization */
	BSP_LCD_Init();

	/* LCD Initialization */
	BSP_LCD_LayerDefaultInit(0, LCD_FB_START_ADDRESS);
	BSP_LCD_LayerDefaultInit(1,
	LCD_FB_START_ADDRESS + (BSP_LCD_GetXSize() * BSP_LCD_GetYSize() * 4));

	/* Enable the LCD */
	BSP_LCD_DisplayOn();

	/* Select the LCD Background Layer  */
	BSP_LCD_SelectLayer(0);

	/* Clear the Background Layer */
	BSP_LCD_Clear(LCD_COLOR_BLACK);

	/* Select the LCD Foreground Layer  */
	BSP_LCD_SelectLayer(1);

	/* Clear the Foreground Layer */
	BSP_LCD_Clear(LCD_COLOR_WHITE);

	/* Configure the transparency for foreground and background :
	 Increase the transparency */
	BSP_LCD_SetTransparency(0, 0);
	BSP_LCD_SetTransparency(1, 100);

	BSP_LCD_SetFont(&Font16);
}

void Display::printf(const char * format, ... )
{
	static int zeile = 0;
	char line[100];
	va_list argptr;
	va_start(argptr, format);
	vsnprintf(line,100,format, argptr);
	va_end(argptr);
	BSP_LCD_DisplayStringAtLine(zeile,(uint8_t*)line);
	zeile=(zeile+1)%16;
}



