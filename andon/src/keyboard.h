#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <stdint.h>
#include "key.h"


class Keyboard
{
	public:
		void setup();
		void tick();
	private:
		unsigned long mLastTickTime;
		Key mKeys[56];
};


#endif


