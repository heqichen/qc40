#ifndef __KEY_H__
#define __KEY_H__

#include <stdint.h>

class Key
{
	public:
		void setup();
		void tick(uint8_t nv);
		uint8_t getNewValue();
		bool hasChanged() const {return mHasChanged;};
	private:
		uint8_t mValue;
		uint8_t	mFlippedCount;
		bool mHasChanged;
};

#endif


