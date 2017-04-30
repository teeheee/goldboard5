#include "goldboard5.h"
#include "i2c.h"

int main(void) {

	goldboard5 gb;
	i2c data(I2C_1);
	while(1)
	{
		data.writeByte(0x41,0);
		gb.delay(500);
	}
}
