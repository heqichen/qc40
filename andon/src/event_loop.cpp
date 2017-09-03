#include "event_loop.h"

#include <hardware_serial.h>
#include <cooboc.h>

#include "keymap.h"
#include "hid_keycode.h"


void EventLoop::setup(Hid *hid, Interpreter *interpreter)
{
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

	const uint8_t *hidBuffer = mInterpreter->getHidKeycodeArray();
	int i;
	for (i=0; i<8; ++i)
	{
		Serial.print(hidBuffer[i], 16);
		Serial.print(" ");
	}
	Serial.println("");
	Serial.print("current layer: ");
	Serial.print(mInterpreter->getCurrentLayerId());
	Serial.println("");
	mHid->sendKeyCode(hidBuffer);

}