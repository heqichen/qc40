#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <stdint.h>
#include "key.h"
#include "event_loop.h"

class Keyboard
{
	public:
		void setup(EventLoop *el);
		void tick();
	private:
		unsigned long mLastTickTime;
		EventLoop *mEventLoop;
		Key mKeys[56];
};


#endif


