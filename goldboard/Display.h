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
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_i2c.h"
#include "i2c.h"
#include <cstdlib>

#define BUFFER_SIZE 255
#define LINES_SIZE  10

//--------------------------------------------------------------
// define ob Multitouch benutzt werden soll oder nicht
// 1 = bis zu 5 Touch-Positionen gleichzeitig
// 0 = nur eine Touchposition
//--------------------------------------------------------------
#define   USE_MULTITOUCH                 1  // mit Multitouch
//#define   USE_MULTITOUCH                 0  // nur Single-Touch

//--------------------------------------------------------------
#define   TOUCH_INIT_DELAY             200  // 200ms
#define   TOUCH_MAX_CONTACT              5  // Multitouch

//--------------------------------------------------------------
#define   TOUCH_MAXX                   480  // Pixel in X
#define   TOUCH_MAXY                   272  // Pixel in Y

//--------------------------------------------------------------
// I2C-Adresse
//--------------------------------------------------------------
#define   FT5336_I2C_ADDR              0x70

//--------------------------------------------------------------
// Register Adressen
//--------------------------------------------------------------
#define   FT5336_STATUS_REG            ((uint8_t)0x02)

#define   FT5336_P1_XH_REG             ((uint8_t)0x03)
#define   FT5336_P1_XL_REG             ((uint8_t)0x04)
#define   FT5336_P1_YH_REG             ((uint8_t)0x05)
#define   FT5336_P1_YL_REG             ((uint8_t)0x06)

#define   FT5336_P2_XH_REG             ((uint8_t)0x09)
#define   FT5336_P2_XL_REG             ((uint8_t)0x0A)
#define   FT5336_P2_YH_REG             ((uint8_t)0x0B)
#define   FT5336_P2_YL_REG             ((uint8_t)0x0C)

#define   FT5336_P3_XH_REG             ((uint8_t)0x0F)
#define   FT5336_P3_XL_REG             ((uint8_t)0x10)
#define   FT5336_P3_YH_REG             ((uint8_t)0x11)
#define   FT5336_P3_YL_REG             ((uint8_t)0x12)

#define   FT5336_P4_XH_REG             ((uint8_t)0x15)
#define   FT5336_P4_XL_REG             ((uint8_t)0x16)
#define   FT5336_P4_YH_REG             ((uint8_t)0x17)
#define   FT5336_P4_YL_REG             ((uint8_t)0x18)

#define   FT5336_P5_XH_REG             ((uint8_t)0x1B)
#define   FT5336_P5_XL_REG             ((uint8_t)0x1C)
#define   FT5336_P5_YH_REG             ((uint8_t)0x1D)
#define   FT5336_P5_YL_REG             ((uint8_t)0x1E)

#define   FT5336_ID_REG                ((uint8_t)0xA8)

//--------------------------------------------------------------
// Status-ID
//--------------------------------------------------------------
#define   FT5336_ID                    0x51

//--------------------------------------------------------------
// Masken
//--------------------------------------------------------------
#define   FT5336_STATUS_MASK           0x0F
#define   FT5336_LO_MASK               0xFF
#define   FT5336_HI_MASK               0x0F

//-----------------------------------------
// Touch-Status
//-----------------------------------------
typedef enum {
	TOUCH_PRESSED = 0,   // Touch ist betaetigt
	TOUCH_RELEASED = 1	// Touch ist nicht betaetigt
} Touch_Status_t;

//-----------------------------------------
// Globale Struktur der Touch-Daten
//-----------------------------------------
typedef struct {
	Touch_Status_t status;
	uint16_t xp;
	uint16_t yp;
} Touch_Data_t;

//-----------------------------------------
// Touch-Position
//-----------------------------------------
typedef struct {
	uint16_t xp;
	uint16_t yp;
} TP_Point_t;

//-----------------------------------------
// Globale Struktur der Multi-Touch-Daten
//-----------------------------------------
typedef struct {
	uint16_t cnt;
	TP_Point_t p[TOUCH_MAX_CONTACT];
} MultiTouch_Data_t;

class Display {
public:
	i2c* I2c;
	Display();
	void printf(const char * format, ...);
	void init(i2c *i2c_);
	void PrintNumAt(uint16_t Xpos, uint16_t Ypos, int16_t num, Text_AlignModeTypdef Mode);
	void PrintNum(uint16_t line, int16_t num);
	void SetTextColor(uint32_t Color);
	void ClearLine(uint32_t Line);
	void StringAt(uint16_t Xpos, uint16_t Ypos, uint8_t *Text,Text_AlignModeTypdef Mode);
	void StringAtLine(uint16_t Line, uint8_t *ptr);

	//--------------------------------------------------------------
	// Globale Funktionen
	//--------------------------------------------------------------
	ErrorStatus UB_Touch_Init(void);
	ErrorStatus UB_Touch_Read(void);

	//--------------------------------------------------------------
	// interne Funktionen
	//--------------------------------------------------------------
	uint8_t P_Touch_ReadID(void);
	uint8_t P_Touch_GetContacts(void);
	uint8_t P_Touch_GetPositions(void);

	MultiTouch_Data_t returnMultiTouch_Data();

	Touch_Data_t returnTouch_Data();
private:
	char* lines[LINES_SIZE];
	char buffer[BUFFER_SIZE];
	int write_position;
	uint8_t FT5336_TOUCH_REG[5][4]; // fuer Register Adressen
	MultiTouch_Data_t MultiTouch_Data;
	Touch_Data_t Touch_Data;

};
//--------------------------------------------------------------

#endif /* DISPLAY_H_ */
