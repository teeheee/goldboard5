#include "goldboard5.h"
#include "serial.h"

goldboard5 gb;

int main(void) {
	serial s;
	while(1)
	{
		gb.delay(100);
		s.sendChar('a');
	}
}
