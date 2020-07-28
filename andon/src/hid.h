#ifndef __HID_H__
#define __HID_H__

#include <stdint.h>

class Hid
{
	public:
		void setup();
		void tick();
		void sendKeyCode(const uint8_t *arr);
		void sendMouse(const uint8_t*arr);
	private:
		void writeHidEndPoint(const uint8_t *data, int length);


};



#endif


