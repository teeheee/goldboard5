/*
 * Display.cpp
 *
 *  Created on: 02.05.2017
 *      Author: alex
 */

#include <Display.h>


Display::Display() {
	for(int i = 0; i < BUFFER_SIZE;i++)
		buffer[i]=0;

	for(int i = 0; i < LINES_SIZE;i++)
		lines[i]=NULL;

	write_position = 0;
}


void Display::init(i2c *i2c_) {
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



MultiTouch_Data_t Display::returnMultiTouch_Data()
{
	return MultiTouch_Data;
}


Touch_Data_t Display::returnTouch_Data()
{
		return Touch_Data;
}

//--------------------------------------------------------------
uint8_t FT5336_TOUCH_REG[5][4]; // fuer Register Adressen


//--------------------------------------------------------------
// Init vom Touch
// Return_wert :
//  -> ERROR   , wenn Touch nicht gefunden wurde
//  -> SUCCESS , wenn Touch OK
//--------------------------------------------------------------
ErrorStatus Display::UB_Touch_Init(void)
{
  uint8_t touch_id=0,n;

  Touch_Data.status=TOUCH_RELEASED;
  Touch_Data.xp=0;
  Touch_Data.yp=0;

  MultiTouch_Data.cnt=0;
  for(n=0;n<TOUCH_MAX_CONTACT;n++) {
    MultiTouch_Data.p[n].xp=0;
    MultiTouch_Data.p[n].yp=0;
  }

  // init der Touch Register Adressen
  FT5336_TOUCH_REG[0][0]=FT5336_P1_XL_REG;
  FT5336_TOUCH_REG[0][1]=FT5336_P1_XH_REG;
  FT5336_TOUCH_REG[0][2]=FT5336_P1_YL_REG;
  FT5336_TOUCH_REG[0][3]=FT5336_P1_YH_REG;

  FT5336_TOUCH_REG[1][0]=FT5336_P2_XL_REG;
  FT5336_TOUCH_REG[1][1]=FT5336_P2_XH_REG;
  FT5336_TOUCH_REG[1][2]=FT5336_P2_YL_REG;
  FT5336_TOUCH_REG[1][3]=FT5336_P2_YH_REG;

  FT5336_TOUCH_REG[2][0]=FT5336_P3_XL_REG;
  FT5336_TOUCH_REG[2][1]=FT5336_P3_XH_REG;
  FT5336_TOUCH_REG[2][2]=FT5336_P3_YL_REG;
  FT5336_TOUCH_REG[2][3]=FT5336_P3_YH_REG;

  FT5336_TOUCH_REG[3][0]=FT5336_P4_XL_REG;
  FT5336_TOUCH_REG[3][1]=FT5336_P4_XH_REG;
  FT5336_TOUCH_REG[3][2]=FT5336_P4_YL_REG;
  FT5336_TOUCH_REG[3][3]=FT5336_P4_YH_REG;

  FT5336_TOUCH_REG[4][0]=FT5336_P5_XL_REG;
  FT5336_TOUCH_REG[4][1]=FT5336_P5_XH_REG;
  FT5336_TOUCH_REG[4][2]=FT5336_P5_YL_REG;
  FT5336_TOUCH_REG[4][3]=FT5336_P5_YH_REG;

  // init vom I2C

  // kleine Pause
  HAL_Delay(TOUCH_INIT_DELAY);

  touch_id=P_Touch_ReadID();
  if(touch_id!=FT5336_ID) return ERROR;

  return(SUCCESS);
}


//--------------------------------------------------------------
// auslesen vom Touch-Status und der Touch-Koordinaten
//
// es kann entweder der Single-Touch "Touch_Data"
// oder der Multi-Touch "MultiTouch_Data" benutzt werden
//
// Return_wert :
//  -> ERROR   , wenn Touch nicht gefunden wurde
//  -> SUCCESS , wenn Touch OK
//
// Touch_Data.status : [TOUCH_PRESSED, TOUCH_RELEASED]
// Touch_Data.xp     : [0...479]
// Touch_Data.yp     : [0...271]
//
// MultiTouch_Data.cnt            : [0...5]
// MultiTouch_Data.p[0..4].xp     : [0...479]
// MultiTouch_Data.p[0..4].yp     : [0...271]
//--------------------------------------------------------------
ErrorStatus Display::UB_Touch_Read(void)
{
  uint8_t check,n;

  // init
  Touch_Data.status=TOUCH_RELEASED;
  Touch_Data.xp=0;
  Touch_Data.yp=0;

  MultiTouch_Data.cnt=0;
  for(n=0;n<TOUCH_MAX_CONTACT;n++) {
    MultiTouch_Data.p[n].xp=0;
    MultiTouch_Data.p[n].yp=0;
  }

  check=P_Touch_GetContacts();
  if(check>TOUCH_MAX_CONTACT) return ERROR;

  if(check>0) {
    // wenn touch betaetigt
    MultiTouch_Data.cnt=check;
    Touch_Data.status=TOUCH_PRESSED;
    check=P_Touch_GetPositions();
    if(check>TOUCH_MAX_CONTACT) {
      // fehler beim lesen
      Touch_Data.status=TOUCH_RELEASED;
      Touch_Data.xp=0;
      Touch_Data.yp=0;

      MultiTouch_Data.cnt=0;
      for(n=0;n<TOUCH_MAX_CONTACT;n++) {
        MultiTouch_Data.p[n].xp=0;
        MultiTouch_Data.p[n].yp=0;
      }
      return ERROR;
    }
    // erste koordinate fuer single touch speichern
    Touch_Data.xp=MultiTouch_Data.p[0].xp;
    Touch_Data.yp=MultiTouch_Data.p[0].yp;
  }

  return(SUCCESS);
}


//--------------------------------------------------------------
// interne Funktion
// ID auslesen (mehrmals versuchen)
// bei Fehler -> return = 0
//--------------------------------------------------------------
uint8_t Display::P_Touch_ReadID(void)
{
  int16_t i2c_wert;
  uint8_t n;

  for(n=0;n<5;n++) {
    i2c_wert=I2c->I2C_ReadByte(FT5336_I2C_ADDR, FT5336_ID_REG);
    if(i2c_wert>0) {
      if((i2c_wert&0xFF)==FT5336_ID) return(FT5336_ID);
    }
  }

  return 0;
}


//--------------------------------------------------------------
// interne Funktion
// anzahl der Touch Kontakte ermitteln
// ret_wert : 0...5 = Anzahl der Kontakte
//               99 = Error
//--------------------------------------------------------------
uint8_t Display::P_Touch_GetContacts(void)
{
  uint8_t ret_wert=0;
  int16_t i2c_wert;

  i2c_wert=I2c->I2C_ReadByte(FT5336_I2C_ADDR, FT5336_STATUS_REG);
  if(i2c_wert<0) return 99;

  // wert maskieren
  ret_wert = (uint8_t)(i2c_wert & FT5336_STATUS_MASK);

  if(ret_wert>TOUCH_MAX_CONTACT) return 0;

  #if USE_MULTITOUCH==0
    // bei Singletouch maximal ein Kontakt
    if(ret_wert>1) ret_wert=1;
  #endif

  return(ret_wert);
}
//--------------------------------------------------------------
// interne Funktion
// die Touch positionen von allen Kontakten ermitteln
// ret_wert :     0 = OK
//               99 = Error
//--------------------------------------------------------------
// interne Funktion
uint8_t Display::P_Touch_GetPositions(void)
{
  uint8_t n,adr,wert_lo,wert_hi;
  int16_t i2c_wert;
  uint16_t position;

  if(MultiTouch_Data.cnt==0) return 0;

  // alle daten einlesen
  for(n=0;n<MultiTouch_Data.cnt;n++) {
    // x_lo
    adr=FT5336_TOUCH_REG[n][0];
    i2c_wert=I2c->I2C_ReadByte(FT5336_I2C_ADDR, adr);
    if(i2c_wert<0) return 99;
    wert_lo = i2c_wert & FT5336_LO_MASK;
    // x_hi
    adr=FT5336_TOUCH_REG[n][1];
    i2c_wert=I2c->I2C_ReadByte(FT5336_I2C_ADDR, adr);
    if(i2c_wert<0) return 99;
    wert_hi = i2c_wert & FT5336_HI_MASK;
    position=(wert_hi<<8)|wert_lo;
    if(position>=TOUCH_MAXY) position=(TOUCH_MAXY-1);
    MultiTouch_Data.p[n].yp=position;
    // y_lo
    adr=FT5336_TOUCH_REG[n][2];
    i2c_wert=I2c->I2C_ReadByte(FT5336_I2C_ADDR, adr);
    if(i2c_wert<0) return 99;
    wert_lo = i2c_wert & FT5336_LO_MASK;
    // y_hi
    adr=FT5336_TOUCH_REG[n][3];
    i2c_wert=I2c->I2C_ReadByte(FT5336_I2C_ADDR, adr);
    if(i2c_wert<0) return 99;
    wert_hi = i2c_wert & FT5336_HI_MASK;
    position=(wert_hi<<8)|wert_lo;
    if(position>=TOUCH_MAXX) position=(TOUCH_MAXX-1);
    MultiTouch_Data.p[n].xp=position;
  }

  return 0;
}

