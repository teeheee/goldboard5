/*
 Wichtige Befehle:
 HAL_GetTick()   --> aktuelle Systemzeit in ms 32 bit! --> millis() geht auch
 HAL_Delay(100); --> normales Delay in ms --> delay(); geht auch
 BSP_LCD_ClearStringLine(0);	--> löscht einzelne Zeilen auf dem Display --> DisplayClearLine(); geht auch
 BSP_LCD_DisplayPrintNum(4,-2);	--> schreibt Zahl "-2" in Zeile 4	-->DisplayPrintNum(); geht auch
 BSP_LCD_DisplayPrintNumAt(50,50,-50,0);	--> Zahl -50 an Position x 50, y 50-->DisplayPrintNumAt(50,50,-50,0); geht auch
 BSP_LCD_DisplayStringAtLine(10, (uint8_t*)"test");   --> String in Zeile 10-->DisplayStringAtLine(10, (uint8_t*)"test");
 BSP_LCD_DisplayStringAt(0,0,"test",0); --> String an Position x0, y0 --> DisplayStringAt(0,0,"test",0); -->geht auch

 ButtonInit(GPIO_PIN_11);     --> Pin 11 als Button
 digitalgetValue(GPIO_PIN_11) --> digitalwert auslesen

 LedInit(GPIO_PIN_1);		  -->Pin1 als Led
 setLed(GPIO_PIN_1,true);	  -->macht led an

 Touch:
 i gibt die Nummer des Fingers an --> 0-4
 vorher die Anzahl der Kontakte auf dem Display auslesen! --> UB_Touch_Read() davor aufrufen!

 UB_Touch_Read();
 BSP_LCD_DisplayPrintNumAt(50,40,MultiTouch_Data.p[i].yp,0);
 BSP_LCD_DisplayPrintNumAt(50,60,MultiTouch_Data.p[i].xp,0);

*/

#include "goldboard5.h"

goldboard5 gb;
//Motor motor;
//PCF8574A pcf8574;

void Kompasstest() ;
void Touchscreentest();
uint8_t val3;

/* Private function prototypes -----------------------------------------------*/
int main(void) {

	/*const char* val = "GoldBoard5";
	const char* val2 = "RoCCI e.V.";
	UB_I2C1_Init();
	UB_Touch_Init();
	#define motpin1 0
	#define motpin2 1
	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_GPIOI_CLK_ENABLE();

	GPIO_InitStruct.Pin = GPIO_PIN_6;			//GPIO_PIN_11
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_SET);
	motor.init(motpin1,motpin2, GPIO_PIN_6, &pcf8574, &val3);




	gb.ButtonInit(GPIO_PIN_11);
	gb.LedInit(GPIO_PIN_1);
	gb.DisplaySetTextColor(LCD_COLOR_RED);
	gb.DisplayStringAtLine(0, (uint8_t*) "STM32F746G-DISCO       ");
	gb.DisplayStringAtLine(9, (uint8_t*) val);
	gb.DisplayStringAtLine(10, (uint8_t*) val2);
	gb.DisplaySetTextColor(LCD_COLOR_LIGHTBLUE);
	BSP_LCD_DrawCircle(350,150,100);
	BSP_LCD_FillCircle(350,150,100);
	gb.DisplaySetTextColor(LCD_COLOR_BROWN);*/

	  GPIO_InitTypeDef  GPIO_InitStruct;
	 GPIO_InitStruct.Pin       = GPIO_PIN_8;
	 GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull      = GPIO_PULLUP;
	  GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
	 // GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin       = GPIO_PIN_9;
	 // GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	  __HAL_RCC_GPIOB_CLK_ENABLE();

	while(1) {
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_8);
		gb.delay(10);
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_9);
		gb.delay(10);
	}
	while (1) {
		//pcf8574.setPin(0,1);
		//gb.delay(100);
		//pcf8574.setPin(0,0);
		//gb.delay(100);
		//motor.rotate(255);
		Touchscreentest();
		Kompasstest();
		//gb.DisplayStringAtLine(6,(uint8_t*)"Taster: ");
		//gb.DisplayPrintNum(7,gb.digitalgetValue(GPIO_PIN_11));
	}
}

/*
#define CompassAdress 0x60
#define CompassReg 3			//3 = wert von 0-359, 2 von 0-3599, 1 von 0-255
#define start 0xC0

int kompassgetValue() {
	UB_I2C3_WriteByte16(CompassAdress, CompassReg, start);
	return UB_I2C3_ReadByte16(CompassAdress,CompassReg);
	/* // send request for new value
		Wire.beginTransmission(CMPS03_I2C_ADDRESS);
		WIRE_WRITE(2);
		Wire.endTransmission();
		Wire.requestFrom(CMPS03_I2C_ADDRESS, 2);

		errorCounter = 0;
		while(Wire.available() < 2) // wait until there is a value
		{
			delay(1);
			errorCounter++;
			// error... infinity loop
			if (errorCounter > CMPS03_ERROR_TIMEOUT)
			{
				return 0;
			}
		}

		// generate return value (high) (low)
		// note: the generated value is from 0 to 3600
		int16_t value = ((int16_t) WIRE_READ()) << 8;
		value = value + ((int16_t) WIRE_READ());

		// convert to values from 0 to 359 (=degrees)
		value /= 10;

		// if there is a 180 degree value, change value that it matches the 180degrees
		if (_180DegreeMode)
		{
	        value += _180DegreeCorrection;
	        if (value >= 360)
	            value = 0 + (value - 360);
	        else if (value < 0)
	            value = 360 + value;
		}

}

void Kompasstest() {
	gb.DisplayStringAtLine(3, (uint8_t*) "Kompasswert: ");
	gb.DisplayPrintNum(4,kompassgetValue());
}

void Touchscreentest() {


	UB_Touch_Read();

	MultiTouch_Data_t MultiTouch_Data = returnMultiTouch_Data();
	Touch_Data_t Touch_Data= returnTouch_Data();

	if (Touch_Data.status == TOUCH_PRESSED) {
		gb.DisplaySetTextColor(LCD_COLOR_LIGHTBLUE);
		BSP_LCD_DrawCircle(350,150,100);
		BSP_LCD_FillCircle(350,150,100);
		for(int i=0;i<P_Touch_GetContacts();i++) {
			if((MultiTouch_Data.p[i].xp > 250) && (MultiTouch_Data.p[i].xp < 450) && (MultiTouch_Data.p[i].yp > 50) && (MultiTouch_Data.p[i].yp < 250)) {
				gb.DisplaySetTextColor(LCD_COLOR_YELLOW);
				BSP_LCD_DrawCircle(350,150,100);
				BSP_LCD_FillCircle(350,150,100);
				gb.DisplaySetTextColor(LCD_COLOR_YELLOW);
			}
		}
		gb.DisplaySetTextColor(LCD_COLOR_BROWN);

		if ((P_Touch_GetContacts() == 1)) {
			if (MultiTouch_Data.p[0].xp > 240) {
				gb.DisplayStringAtLine(1, (uint8_t*) "Rechts ");
			}
			else {
				gb.DisplayStringAtLine(1, (uint8_t*) "Links ");
			}
		}
		else {
			gb.DisplayStringAtLine(1, (uint8_t*) "Zu viele Finger ");
		}
	}
	else {
		gb.DisplaySetTextColor(LCD_COLOR_LIGHTBLUE);
		BSP_LCD_DrawCircle(350,150,100);
		BSP_LCD_FillCircle(350,150,100);
		gb.DisplaySetTextColor(LCD_COLOR_BROWN);
		gb.DisplayStringAtLine(1, (uint8_t*) "nicht gedrueckt ");
	}
	uint8_t finger = P_Touch_GetContacts();

	if (finger == 0) {
		gb.DisplayStringAtLine(0, (uint8_t*) "IS DES TOUCH?? ");
	}
	else if (finger == 1) {
		gb.DisplayStringAtLine(0, (uint8_t*) "1 Finger wurde aufgelegt ");
	}
	else if (finger == 2) {
		gb.DisplayStringAtLine(0, (uint8_t*) "2 Finger wurden aufgelegt ");
	}
	else if (finger == 3) {
		gb.DisplayStringAtLine(0, (uint8_t*) "3 Finger wurden aufgelegt ");
	}
	else if (finger == 4) {
		gb.DisplayStringAtLine(0, (uint8_t*) "4 Finger wurden aufgelegt ");
	}
	else {
		gb.DisplayStringAtLine(0, (uint8_t*) "5 Finger wurden aufgelegt ");
	}
	HAL_GPIO_TogglePin(GPIOI, GPIO_PIN_1);
	gb.delay(100);
	gb.DisplayClearLine(0);
	gb.DisplayClearLine(1);
}*/

