#include "bmx055.h"

#include "hardware_iic.h"

#include <stdint.h>

#define BMX055_ADDR   0x18
uint8_t i2cBuffer[8];
bool readBmx055Acc(uint8_t regAddr, int16_t *axis)
{
	bool ok = false;
	i2cBuffer[0] = regAddr;
	ok = Iic1.write(BMX055_ADDR, i2cBuffer, 1);
	if (ok)
	{
		ok = Iic1.read(BMX055_ADDR, i2cBuffer, 2);
		if (ok)
		{
			int8_t lsb = i2cBuffer[0];
			int8_t msb = i2cBuffer[1];
			*axis = ((int16_t)msb) << 8;
			*axis >>= 4;
			lsb &= 0x0F;
			*axis |= lsb;
		}
	}
	return ok;
}
bool readBmx055AccX(int16_t *x)
{
	return readBmx055Acc(0x02, x);
}
bool readBmx055AccY(int16_t *y)
{
	return readBmx055Acc(0x04, y);
}
bool readBmx055AccZ(int16_t *z)
{
	return readBmx055Acc(0x06, z);
}
