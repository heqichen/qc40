#ifndef __HID_H__
#define __HID_H__

#include <stdint.h>

class Hid
{
	public:
		void setup();
		void tick();
		void sendKeyCode(const uint8_t *arr);
	private:


};



#endif


