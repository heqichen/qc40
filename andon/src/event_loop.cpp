#include "event_loop.h"

#include <hardware_serial.h>
#include <cooboc.h>

#include "keymap.h"
#include "hid_keycode.h"


void EventLoop::setup(Hid *hid, Interpreter *interpreter)
{
	mLastReportTime = 0;
	mFifo.setup(24);
	mHid = hid;
	mInterpreter = interpreter;
	mHid->setup();
	mInterpreter->setup();

}

void EventLoop::tick()
{
	mHid->tick();
	mInterpreter->tick();

	while (mFifo.size() > 0)
	{
		uint32_t vv = mFifo.pop();
		uint8_t type = vv >> 24;
		int value = vv & 0x00FFFFFF;
		this->dispatcher(type, value);
	}

	reportHid();
	
}

void EventLoop::reportHid()
{
	if (millis() - mLastReportTime < 10)
	{
		return ;
	}
	mLastReportTime = millis();

	const uint8_t *hidBuffer ;
	int i;
	if (mInterpreter->isKeyboardDirty())
	{
		Serial.print("keyboard: \t");
		hidBuffer= mInterpreter->getHidKeycodeArray();
		
		for (i=0; i<8; ++i)
		{
			Serial.print(hidBuffer[i], 16);
			Serial.print(" ");
		}
		Serial.println("");
		mHid->sendKeyCode(hidBuffer);
		return ;
	}


	if (mInterpreter->isMouseDirty())
	{
		Serial.print("Mouse: \t");
		hidBuffer = mInterpreter->getMouseEvent();
		for (i=0; i<4; ++i)
		{
			Serial.print(hidBuffer[i], 16);
			Serial.print(" ");
		}
		Serial.println("");
		mHid->sendMouse(hidBuffer);
	}
}

void EventLoop::newEvent(uint8_t type, int value)
{
	uint32_t oo = (((uint32_t)type) << 24) | (value & 0x00FFFFFF);
	mFifo.push(oo);
}

void EventLoop::dispatcher(uint8_t type, int value)
{
	switch (type)
	{
		case (EVENT_KEY_DOWN):
		{
			mInterpreter->onKeyDown(value);
			break;
		}
		case (EVENT_KEY_UP):
		{
			mInterpreter->onKeyUp(value);
			break;
		}
		default:
		{
			break;
		}
	}



	
	Serial.print("current layer: ");
	Serial.print(mInterpreter->getCurrentLayerId());
	Serial.println("");

}