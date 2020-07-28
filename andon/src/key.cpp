#include "key.h"

void Key::setup()
{
	mValue = 0xFF;
	mFlippedCount = 0;
	mHasChanged = false;
}

void Key::tick(uint8_t nv)
{
	if (mValue == 0xFF)
	{
		mValue = nv;
		return ;
	}


	if (nv != mValue)
	{
		mFlippedCount++;
		if (mFlippedCount > 2)
		{
			mValue = nv;
			mFlippedCount = 0;
			mHasChanged = true;
		}
	}
}

uint8_t Key::getNewValue()
{
	mHasChanged = false;
	return mValue;
}



