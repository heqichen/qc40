#include "hid.h"
#include <cooboc.h>
#include <hardware_serial.h>

#include "hw_config.h"

void Hid::setup()
{

}

void Hid::tick(void)
{

}

extern __IO uint8_t PrevXferComplete;

void Hid::sendKeyCode(const uint8_t *arr)
{
	uint8_t buffer[9];
	buffer[0] = 0x01;
	int i;
	for (i=0; i<8; ++i)
	{
		buffer[i+1] = arr[i];
	}

	while (!PrevXferComplete)
	{

	}
	if (bDeviceState == CONFIGURED)
	{
		sendKeyboardData(buffer, 9);
	}
}