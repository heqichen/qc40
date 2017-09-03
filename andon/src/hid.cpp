#include "hid.h"
#include <cooboc.h>
#include <hardware_serial.h>

#include "hw_config.h"

void Hid::setup()
{
	int i, j;
	for (j=0; j<3; ++j)
	{
		mKeyboardBuffer[j][0] = 0x01;	//report id
		for (i=1; i<10; ++i)
		{
			mKeyboardBuffer[j][i] = 0x00;
		}
	}
	mLastReportTime = millis();
}

void Hid::tick(void)
{

	int i, j;
	if (millis() - mLastReportTime < 1000)
	{
		return ;
	}

	mLastReportTime = millis();

	if (mKeyboardBuffer[1][9] == 0)
	{
		return ;
	}
	/*
	while (!PrevXferComplete)
	{

	}
	if (bDeviceState == CONFIGURED)
	{
		sendKeyboardData(data, 5);
	}
	*/
	for (j=0; j<2; ++j)
	{
		for (i=0; i<10; ++i)
		{
			mKeyboardBuffer[j][i] = mKeyboardBuffer[j+1][i];
		}
	}
	mKeyboardBuffer[2][0] = 0x01;	//report id
	for (i=1; i<9; ++i)
	{
		mKeyboardBuffer[2][i] = mKeyboardBuffer[1][i];
	}
	mKeyboardBuffer[2][9] = 0x00;

	for (j=0; j<3; ++j)
	{
		for (i=0; i<10; ++i) 
		{
			Serial.print(mKeyboardBuffer[j][i], 16);
			Serial.print(" ");
		}
		Serial.print("\t");
	}
	Serial.println();
	

}

void Hid::keyDown(uint8_t kc)
{
	if (!isKeyboardBufferContainKey(0, kc))
	{
		addKeyToKeyboardBuffer(1, kc);
		mKeyboardBuffer[1][9] = 0x01;
		addKeyToKeyboardBuffer(2, kc);
	}
}

void Hid::keyUp(uint8_t kc)
{
	if (isKeyboardBufferContainKey(0, kc))
	{
		//TODO
	}
	else
	{
		if (isKeyboardBufferContainKey(1, kc))
		{
			removeKeyFromKeyboardBuffer(1, 1);
		}
		else
		{
			
		}
	}
}

bool Hid::isKeyboardBufferContainKey(int bufferId, uint8_t kc)
{
	int i;
	for (i=3; i<9; ++i)
	{
		if (mKeyboardBuffer[bufferId][i] == kc)
		{
			return true;
		}
	}
	return false;
}

void Hid::addKeyToKeyboardBuffer(int bufferId, uint8_t kc)
{
	int i;
	for (i=3; i<9; ++i)
	{
		if (mKeyboardBuffer[bufferId][i] == kc)
		{
			//already added
			return;
		}
		if (mKeyboardBuffer[bufferId][i] == 0x00)
		{
			mKeyboardBuffer[bufferId][i] = kc;
			return ;
		}
	}
	//over flow
}

void Hid::removeKeyFromKeyboardBuffer(int bufferId, uint8_t kc)
{
	int i;
	for (i=3; i<9; ++i)
	{
		if (mKeyboardBuffer[bufferId][i] == kc)
		{
			break;
		}
	}
	while (i<9)
	{
		mKeyboardBuffer[bufferId][i] = mKeyboardBuffer[bufferId][i+1];
		++i;
	}
	mKeyboardBuffer[bufferId][8] = 0x00;
}