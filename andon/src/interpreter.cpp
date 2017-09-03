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
		case (EVENT_VALUE_KEYMOD):
		{
			addKeycode(phyKey, keyFun);
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

void Interpreter::addKeycode(uint8_t phyKey, int keycode)
{
	mActivePhyKey[mKbMapLength] = phyKey;
	mActiveKeycode[mKbMapLength] = keycode;
	mKbMapLength++;	

}
void Interpreter::removeKeycode(uint8_t phyKey)
{
	int i;
	for (i=0; i<mKbMapLength; ++i)
	{
		if (mActivePhyKey[i] == phyKey)
		{
			break;
		}
	}
	while (i<mKbMapLength-1)
	{
		mActivePhyKey[i] = mActivePhyKey[i+1];
		mActiveKeycode[i] = mActiveKeycode[i+1];
		++i;
	}
	--mKbMapLength;
}

const uint8_t *Interpreter::getHidKeycodeArray()
{
	int i, j;
	int kcLength = 0;

	//step 1. intitialize
	for (i=0; i<7; ++i)
	{
		mHidKeycodes[i] = KEYCODE_NONE;
 	}

 	
 	for (i=0; i<mKbMapLength; ++i)
 	{
 		
 		int kc = mActiveKeycode[i];
 		int keyType = kc & EVENT_VALUE_MASK;
 		uint8_t hidKc = kc & 0xFF;
 		switch (keyType)
 		{
 			case (EVENT_VALUE_KEYCODE):
 			{
 				//step 2. check duplicated
		 		for (j=0; j<kcLength; ++j)
		 		{
		 			if (hidKc == mHidKeycodes[1+j])
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
		 				mHidKeycodes[1+j] = KEYCODE_ERR_OVF;
		 			}
		 			break;
		 		}

		 		mHidKeycodes[1+kcLength] = hidKc;
		 		kcLength++;
 				break;
 			}
 			case (EVENT_VALUE_KEYMOD):
 			{

 				break;
 			}
 			default:
 			{
 				break;
 			}
 		}


 	}
 	return mHidKeycodes;
}
