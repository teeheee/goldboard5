#include "goldboard5.h"
#include "serial.h"


int main(void) {
	goldboard5 gb;
	serial s;
	s.init(6,9600);
	while(1)
	{
		gb.delay(100);
		s.sendChar('a');
	}
}
