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

	writeHidEndPoint(buffer, 9);


}

void Hid::sendMouse(const uint8_t*arr)
{
	uint8_t buffer[5];
	buffer[0] = 0x02;
	int i;
	for (i=0; i<4; ++i)
	{
		buffer[1+i] = arr[i];
	}
	writeHidEndPoint(buffer, 5);
}


void Hid::writeHidEndPoint(const uint8_t *data, int length)
{
	while (!PrevXferComplete)
	{
		Serial.write('.');
	}
	if (bDeviceState == CONFIGURED)
	{
		sendHidData(data, length);
	}
}