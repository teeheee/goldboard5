#include "goldboard5.h"
#include "Display.h"
#include "serial.h"
//#include "HC05.h"

goldboard5 gb;

int main(void) {
	Display d;
	serial s;
	s.init(UART6,38400UL);
	s.sendString((uint8_t*)"AT\r\n");
	while(1)
	{
		d.printf("AT: %c",s.getChar());
		gb.delay(1000);
	}
}
