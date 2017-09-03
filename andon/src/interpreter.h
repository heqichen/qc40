#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include <stdint.h>

class Interpreter
{
	public:
		void setup();
		void tick();
		void onKeyDown(uint8_t phyKey);
		void onKeyUp(uint8_t phyKey);
		const uint8_t *getHidKeycodeArray();
	private:
		uint8_t mActivePhyKey[60];
		uint32_t mActiveKeyFun[60];

		uint8_t mHidKeycodes[8];
		int mKbMapLength;

		void addKeycode(uint8_t phyKey, uint32_t keyFun);
		void removeKeycode(uint8_t phyKey);
};


#endif


