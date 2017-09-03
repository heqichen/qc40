#include "interpreter.h"

#include <hardware_serial.h>
#include "keymap.h"
#include "hid_keycode.h"
#include "keycode.h"

void Interpreter::setup()
{
	mKbMapLength = 0;
}

void Interpreter::tick()
{

}


void Interpreter::onKeyDown(uint8_t phyKey)
{
	uint32_t keyFun = mmmap[phyKey];
	uint32_t eventValue = keyFun & EVENT_VALUE_MASK;
	
	switch (eventValue)
	{
		case (EVENT_VALUE_KEYCODE):
		{
			uint8_t keycode = keyFun & 0xFF;
			addKeycode(phyKey, keycode);
			break;
		}
		default:
		{
			//TODO
			break;
		}
	}

	
}


void Interpreter::onKeyUp(uint8_t phyKey)
{
	removeKeycode(phyKey);
}

void Interpreter::addKeycode(uint8_t phyKey, uint8_t keyCode)
{
	mPhy2Code[mKbMapLength][0] = phyKey;
	mPhy2Code[mKbMapLength][1] = keyCode;
	mKbMapLength++;	
}
void Interpreter::removeKeycode(uint8_t phyKey)
{
	int i;
	for (i=0; i<mKbMapLength; ++i)
	{
		if (mPhy2Code[i][0] == phyKey)
		{
			break;
		}
	}
	while (i<mKbMapLength-1)
	{
		mPhy2Code[i][0] = mPhy2Code[i+1][0];
		mPhy2Code[i][1] = mPhy2Code[i+1][1];
		++i;
	}
	--mKbMapLength;
}

const uint8_t *Interpreter::getHidKeycodeArray()
{
	int i, j;
	int kcLength = 0;

	//step 1. intitialize
	for (i=0; i<6; ++i)
	{
		mHidKeycodes[i] = KEYCODE_NONE;
 	}

 	
 	for (i=0; i<mKbMapLength; ++i)
 	{
 		//step 2. check duplicated
 		uint8_t kc = mPhy2Code[i][1];
 		for (j=0; j<kcLength; ++j)
 		{
 			if (kc == mHidKeycodes[j])
 			{
 				break;
 			}
 		}

 		if (j<kcLength && kcLength>0)
 		{
 			continue;
 		}


 		//step 3, check overflow
 		if (kcLength == 6)
 		{
 			for (j=0; j<6; ++j)
 			{
 				mHidKeycodes[j] = KEYCODE_ERR_OVF;
 			}
 			break;
 		}

 		mHidKeycodes[kcLength] = kc;
 		kcLength++;
 	}
 	return mHidKeycodes;
}
