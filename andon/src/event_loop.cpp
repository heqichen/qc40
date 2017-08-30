#include "event_loop.h"

#include <hardware_serial.h>

void EventLoop::setup()
{
	mFifo.setup(24);
}

void EventLoop::tick()
{
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
			Serial.print("key down: ");
			Serial.println(value);
			break;
		}
		case (EVENT_KEY_UP):
		{
			Serial.print("key up: ");
			Serial.println(value);
			break;
		}
		default:
		{
			break;
		}
	}
}