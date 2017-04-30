#include "goldboard5.h"

goldboard5 gb;

int main(void) {
	while(1)
	{
		gb.delay(100);
		gb.motors[0].rotate(100);
		gb.delay(100);
		gb.motors[0].rotate(-100);
		gb.delay(100);
		gb.motors[0].rotate(0);
		gb.motors[1].rotate(100);
		gb.delay(100);
		gb.motors[1].rotate(-100);
		gb.delay(100);
		gb.motors[1].rotate(0);
		gb.motors[2].rotate(100);
		gb.delay(100);
		gb.motors[2].rotate(-100);
		gb.delay(100);
		gb.motors[2].rotate(0);
		gb.motors[3].rotate(100);
		gb.delay(100);
		gb.motors[3].rotate(-100);
		gb.delay(100);
		gb.motors[3].rotate(0);
		gb.delay(1000);
	}
}
