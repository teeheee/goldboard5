/*
 * goldboard5.cpp
 * */

#include "goldboard5.h"



goldboard5::goldboard5()
{
	HAL_Init();
	SystemClock_Config();
	BSP_LED_Init(LED1);
	DisplayConfig();
}


void goldboard5::setLed(bool state)
{
	if(state)
		BSP_LED_On(LED1);
	else
		BSP_LED_Off(LED1);
}



void goldboard5::ButtonInit(uint16_t PIN) {

	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_GPIOI_CLK_ENABLE();

	GPIO_InitStruct.Pin  = PIN;			//GPIO_PIN_11
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);
}

void goldboard5::LedInit(uint16_t PIN) {

	BSP_LED_Init(LED1);
}


uint8_t goldboard5::digitalgetValue(uint16_t GPIO_Pin) {
	return HAL_GPIO_ReadPin(GPIOI,GPIO_Pin);
}

void goldboard5::DisplayStringAtLine(uint16_t Line, uint8_t *ptr) {
	BSP_LCD_DisplayStringAtLine(Line, ptr);
}

void goldboard5::DisplayStringAt(uint16_t Xpos, uint16_t Ypos, uint8_t *Text, Text_AlignModeTypdef Mode) {
	BSP_LCD_DisplayStringAt(Xpos,Ypos,Text,Mode);
}

void goldboard5::DisplayClearLine(uint32_t Line) {
	BSP_LCD_ClearStringLine(Line);
}

void goldboard5::DisplaySetTextColor(uint32_t Color) {
	BSP_LCD_SetTextColor(Color);
}

void goldboard5::DisplayPrintNum(uint16_t line, int16_t num) {
	int v = 0;
	itoa(num, (char*) v, 10);			//num wird zur Basis 10 in v gespeichert
	BSP_LCD_DisplayStringAtLine(line, (uint8_t*) v);
}

void goldboard5::DisplayPrintNumAt(uint16_t Xpos, uint16_t Ypos, int16_t num, Text_AlignModeTypdef Mode) {
	char v[100];
	itoa(num, v, 10);			//num wird zur Basis 10 in v gespeichert
	BSP_LCD_DisplayStringAt(Xpos, Ypos, (uint8_t*) v, Mode);
}

void goldboard5::DisplayConfig() {
	/* LCD Initialization */
	BSP_LCD_Init();

	/* LCD Initialization */
	BSP_LCD_LayerDefaultInit(0, LCD_FB_START_ADDRESS);
	BSP_LCD_LayerDefaultInit(1,
			LCD_FB_START_ADDRESS
					+ (BSP_LCD_GetXSize() * BSP_LCD_GetYSize() * 4));

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

/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow :
 *            System Clock source            = PLL (HSE)
 *            SYSCLK(Hz)                     = 200000000
 *            HCLK(Hz)                       = 200000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 4
 *            APB2 Prescaler                 = 2
 *            HSE Frequency(Hz)              = 25000000
 *            PLL_M                          = 25
 *            PLL_N                          = 400
 *            PLL_P                          = 2
 *            PLL_Q                          = 8
 *            VDD(V)                         = 3.3
 *            Main regulator output voltage  = Scale1 mode
 *            Flash Latency(WS)              = 6
 * @param  None
 * @retval None
 */
void goldboard5::Delay(__IO uint32_t Delay) {
	HAL_Delay(Delay);
}

void goldboard5::DisplayClear() {
	for (uint8_t i = 0; i < 11; i++) {
		DisplayClearLine(i);
	}
}
uint32_t goldboard5::millis() {
	return HAL_GetTick();
}




void goldboard5::SystemClock_Config() {
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;
	HAL_StatusTypeDef ret = HAL_OK;

	/* Enable HSE Oscillator and activate PLL with HSE as source*/
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 25;
	RCC_OscInitStruct.PLL.PLLN = 400;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 8;

	ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
	if (ret != HAL_OK) {
		while (1) {
			;
		}
	}

	/* Activate the OverDrive to reach the 200 MHz Frequency
	 ret = HAL_PWREx_EnableOverDrive();
	 if(ret != HAL_OK)
	 {
	 while(1) { ; }
	 }*/

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers*/
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_6);
	if (ret != HAL_OK) {
		while (1) {
			;
		}
	}
}

