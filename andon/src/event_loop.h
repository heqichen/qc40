#ifndef __EVENT_LOOP_H__
#define __EVENT_LOOP_H__

#include "fifo.h"


#define EVENT_KEY_DOWN	0x01
#define EVENT_KEY_UP	0x02

class EventLoop
{
	public:
		void setup();
		void tick();
		void newEvent(uint8_t type, int value);
	private:
		void dispatcher(uint8_t type, int value);
		Fifo mFifo;

};


#endif 


