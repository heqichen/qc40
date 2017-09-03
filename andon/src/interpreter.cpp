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
			Serial.print("add ");
			Serial.print(phyKey);
			Serial.print(" ");
			Serial.print(keyFun);
			Serial.println("");
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

void Interpreter::addKeycode(uint8_t phyKey, uint32_t keyFun)
{
	mActivePhyKey[mKbMapLength] = phyKey;
	mActiveKeyFun[mKbMapLength] = keyFun;
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
		mActiveKeyFun[i] = mActiveKeyFun[i+1];
		++i;
	}
	--mKbMapLength;
}

const uint8_t *Interpreter::getHidKeycodeArray()
{
	int i, j;
	int kcLength = 0;

	//step 1. intitialize
	for (i=0; i<8; ++i)
	{
		mHidKeycodes[i] = KEYCODE_NONE;
 	}

 	
 	for (i=0; i<mKbMapLength; ++i)
 	{
 		
 		int kc = mActiveKeyFun[i];
 		int keyType = kc & EVENT_VALUE_MASK;
 		uint8_t hidKc = kc & 0xFF;
 		switch (keyType)
 		{
 			case (EVENT_VALUE_KEYCODE):
 			{
 				//step 2. check duplicated
		 		for (j=0; j<kcLength; ++j)
		 		{
		 			if (hidKc == mHidKeycodes[2+j])
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
		 				mHidKeycodes[2+j] = KEYCODE_ERR_OVF;
		 			}
		 			break;
		 		}

		 		mHidKeycodes[2+kcLength] = hidKc;
		 		kcLength++;
 				break;
 			}
 			case (EVENT_VALUE_KEYMOD):
 			{
 				mHidKeycodes[0] |= hidKc;
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
