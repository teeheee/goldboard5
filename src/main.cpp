#include "goldboard5.h"
#include "i2c.h"

goldboard5 gb;

int main(void) {


	i2c bus(I2C_1);
	while (1)
	{
		bus.writeByte(0x42,0x42);
		gb.setLed(true);
		gb.delay(100);
		gb.setLed(false);
		gb.delay(100);
	}
}
