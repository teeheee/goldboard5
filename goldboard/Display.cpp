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
	BSP_LCD_Clear(LCD_COLOR_BLACK);

	/* Configure the transparency for foreground and background :
	 Increase the transparency */
	BSP_LCD_SetTransparency(0, 0);
	BSP_LCD_SetTransparency(1, 100);
}

void Display::printf(const char * format, ... )
{
	char line[100];
	va_list argptr;
	va_start(argptr, format);
	int n = vsnprintf(line,100,format, argptr);
	va_end(argptr);

	if(n<100)
	{
		if(BUFFER_SIZE-write_position>n)
		{
			memcpy(&buffer[write_position],line,n);
			write_position+=n;
		}
		else
		{
			int end = BUFFER_SIZE-write_position;
			memcpy(&buffer[write_position],line,end);
			memcpy(buffer,line+end,n-end);
			write_position=n-end;
		}
	}
	int x_column = 0;
	int y_line = 0;
	int fontheight =  (((sFONT *)BSP_LCD_GetFont())->Height);
	int fontwidth =  (((sFONT *)BSP_LCD_GetFont())->Width);
	for(int i = write_position;i != write_position-1; i=(i+BUFFER_SIZE+1)%BUFFER_SIZE)
	{
		if(buffer[i]!=0 && buffer[i]!='\r')
		{
			if(buffer[i]=='\n')
			{
				y_line=(y_line+1)%10;
				x_column=0;
			}
			else
			{
				BSP_LCD_DisplayChar(x_column*fontwidth,y_line*fontheight,buffer[i]);
				x_column++;
			}
		}
	}
}



