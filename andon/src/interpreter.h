#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include <stdint.h>

class Interpreter
{
	public:
		void setup();
		void tick();
		void onKeyDown(uint8_t phyKey);
		const uint8_t *getHidKeycodeArray();
	private:
		uint8_t mPhy2Code[60][2];
		uint8_t mHidKeycodes[6];
		int mKbMapLength;
};


#endif


