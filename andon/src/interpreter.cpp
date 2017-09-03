#include "interpreter.h"

#include <hardware_serial.h>
#include "keymap.h"
#include "hid_keycode.h"

void Interpreter::setup()
{
	mKbMapLength = 0;
}

void Interpreter::tick()
{

}


void Interpreter::onKeyDown(uint8_t phyKey)
{
	Serial.print("key down: ");
	uint8_t simKc = mmmap[phyKey];
	mPhy2Code[mKbMapLength][0] = phyKey;
	mPhy2Code[mKbMapLength][1] = simKc;
	mKbMapLength++;


	Serial.print(simKc, 16);
	Serial.println("");
	
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
