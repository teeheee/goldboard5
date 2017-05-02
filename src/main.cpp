#include "goldboard5.h"
#include "Display.h"

goldboard5 gb;

int main(void) {
	Display d;
	int x = 0;
	while(1)
	{
		d.printf("Sekunde: %d\r\n",x);
		x++;
		gb.delay(1000);
	}
}
