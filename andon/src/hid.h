#ifndef __HID_H__
#define __HID_H__

#include <stdint.h>

class Hid
{
	public:
		void setup();
		void tick();
		void keyDown(uint8_t kc);
		void keyUp(uint8_t kc);
	private:
		uint8_t mKeyboardBuffer[3][10];	//0: last sent packet, 1: next send packet, 2: second send packet
		unsigned long mLastReportTime;
		bool isKeyboardBufferContainKey(int bufferId, uint8_t kc);
		void addKeyToKeyboardBuffer(int bufferId, uint8_t kc);
		void removeKeyFromKeyboardBuffer(int bufferId, uint8_t kc);


};



#endif


