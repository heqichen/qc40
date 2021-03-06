#include "interpreter.h"

#include <hardware_serial.h>
#include <cooboc.h>

#include "keymap.h"
#include "hid_keycode.h"
#include "keycode.h"

void Interpreter::setup()
{
	mLastTickTime = 0UL;
	mKbMapLength = 0;
	mLayerLength = 0;
	mMouseEventLength = 0;
	mIsKeyboardDirty = false;
	mIsMouseDirty = false;
	mMousePosX = 0;
	mMousePosY = 0;
	mLastMouseMoveTime = 0UL;
}

void Interpreter::tick()
{
	if (millis() - mLastTickTime < 2)
	{
		return; 
	}
	mLastTickTime = millis();

	refreshMouse();
}

void Interpreter::refreshMouse()
{
	int i;
	if (millis() - mLastMouseMoveTime < 20)
	{
		return ;
	}
	mLastMouseMoveTime = millis();
	//Serial.print("mouse event length: ");
	//Serial.println(mMouseEventLength);

	for (i=0; i<mMouseEventLength; ++i)
	{
		Serial.print(mMouseEvnetMap[i][1]);
		Serial.println(":  ");
		switch (mMouseEvnetMap[i][1])
		{
			case (MOUSE_EVENT_MOVE_UP):
			{
				mMousePosY -= 3;
				mIsMouseDirty = true;
				break;
			}
			case (MOUSE_EVENT_MOVE_DOWN):
			{
				mMousePosY += 3;
				Serial.println(mMousePosY);
				mIsMouseDirty = true;
				break;
			}
			case (MOUSE_EVENT_MOVE_LEFT):
			{
				mMousePosX -= 3;
				mIsMouseDirty = true;
				break;
			}
			case (MOUSE_EVENT_MOVE_RIGHT):
			{
				mMousePosX += 3;
				mIsMouseDirty = true;
				break;
			}
			default:
			{
				break;
			}
		}
	}
	
}

uint32_t Interpreter::getKeyFun(uint8_t phyKey)
{
	Serial.print("Layer: [");
	int i;
	for (i=0; i<mLayerLength; ++i)
	{
		Serial.print(mLayerStackMap[i][1]);
		Serial.print(" , ");
	}
	Serial.println("   ]");
	int keyFun = 0x00;
	int layerIp = mLayerLength-1;

	while (layerIp >= 0)
	{

		int layerId = mLayerStackMap[layerIp][1];
		Serial.print(layerIp);
		Serial.print("#");
		Serial.print(layerId);
		Serial.println("");
		keyFun = myLayout[layerId][phyKey];
		if (KB_____ != keyFun)
		{
			Serial.print("find key at: ");
			Serial.print(layerIp);
			Serial.println("");
			return keyFun;
		}
		--layerIp;
	}
	
	return myLayout[0][phyKey];
}


void Interpreter::onKeyDown(uint8_t phyKey)
{
	
	uint32_t keyFun = getKeyFun(phyKey);
	uint32_t eventValue = keyFun & EVENT_VALUE_MASK;
	
	switch (eventValue)
	{

		case (EVENT_VALUE_KEYCODE):
		case (EVENT_VALUE_KEYMOD):
		{
			addKeycode(phyKey, keyFun);
			mIsKeyboardDirty = true;
			break;
		}
		case (EVENT_VALUE_LAYER):
		{
			uint8_t layerId = keyFun & 0xFF;
			addLayer(phyKey, layerId);
			break;
		}
		case (EVENT_VALUE_MOUSE):
		{
			uint8_t value = keyFun & 0xFF;
			Serial.print("add mouse event: ");
			Serial.print(value, 16);
			Serial.println("");
			addMouseEvent(phyKey, value);
			mIsMouseDirty = true;
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
	if (removeKeycode(phyKey))
	{
		mIsKeyboardDirty = true;
	}
	removeLayer(phyKey);
	if (removeMouseEvent(phyKey))
	{
		mIsMouseDirty = true;
	}
}

void Interpreter::addKeycode(uint8_t phyKey, uint32_t keyFun)
{
	mActivePhyKey[mKbMapLength] = phyKey;
	mActiveKeyFun[mKbMapLength] = keyFun;
	mKbMapLength++;	
}
bool Interpreter::removeKeycode(uint8_t phyKey)
{
	int i;
	for (i=0; i<mKbMapLength; ++i)
	{
		if (mActivePhyKey[i] == phyKey)
		{
			break;
		}
	}
	while (i < mKbMapLength-1)
	{
		mActivePhyKey[i] = mActivePhyKey[i+1];
		mActiveKeyFun[i] = mActiveKeyFun[i+1];
		++i;
	}

	if (i < mKbMapLength)
	{
		--mKbMapLength;
		return true;
	}
	return false;
	
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
 	mIsKeyboardDirty = false;
 	return mHidKeycodes;
}



void Interpreter::addLayer(uint8_t phyKey, uint8_t layerId)
{
	if (mLayerLength >= MAX_LAYER_DEPTH)
	{
		return ;
	}

	mLayerStackMap[mLayerLength][0] = phyKey;
	mLayerStackMap[mLayerLength][1] = layerId;
	++mLayerLength;
}


void Interpreter::removeLayer(uint8_t phyKey)
{
	int i;
	for (i=0; i<mLayerLength; ++i)
	{
		if (mLayerStackMap[i][0] == phyKey)
		{
			mLayerStackMap[i][0] = 0xFF;
		}
	}

	i = mLayerLength-1;
	while (i>=0)
	{
		if (mLayerStackMap[i][0] != 0xFF)
		{
			break;
		}
		--i;
	}
	mLayerLength = i+1;
}


int Interpreter::getCurrentLayerId()
{
	if (mLayerLength > 0)
	{
		return mLayerStackMap[mLayerLength-1][1];
	}
	else
	{
		return 0;
	}
}

void Interpreter::addMouseEvent(uint8_t phyKey, uint8_t event)
{
	if (mMouseEventLength > 8)
	{
		return ;
	}
	mLastMouseMoveTime = 0;
	mMouseEvnetMap[mMouseEventLength][0] = phyKey;
	mMouseEvnetMap[mMouseEventLength][1] = event;
	++mMouseEventLength;
}

bool Interpreter::removeMouseEvent(uint8_t phyKey)
{
	int i;
	for (i=0; i<mMouseEventLength; ++i)
	{
		if (mMouseEvnetMap[i][0] == phyKey)
		{
			break;
		}
	}
	while (i < mMouseEventLength-1)
	{
		mMouseEvnetMap[i][0] = mMouseEvnetMap[i+1][0];
		mMouseEvnetMap[i][1] = mMouseEvnetMap[i+1][1];
		++i;
	}
	if (i < mMouseEventLength)
	{
		--mMouseEventLength;
		return true;
	}
	return false;
}

const uint8_t * Interpreter::getMouseEvent()
{
	int i;
	for (i=0; i<4; ++i)
	{
		mHidMouse[i] = 0x00;
	}
	for (i=0; i<mMouseEventLength; ++i)
	{
		switch (mMouseEvnetMap[i][1])
		{
			case (MOUSE_EVENT_LEFT_BUTTON):
			{
				mHidMouse[0] |= 0x01;
				break;
			}
			case (MOUSE_EVENT_MIDDLE_BUTTON):
			{
				mHidMouse[0] |= 0x02;
				break;
			}
			case (MOUSE_EVENT_RIGHT_BUTTON):
			{
				mHidMouse[0] |= 0x04;
				break;
			}
			case (MOUSE_EVENT_MOVE_UP):
			case (MOUSE_EVENT_MOVE_DOWN):
			{
				mHidMouse[2] = mMousePosY;
				break;
			}
			case (MOUSE_EVENT_MOVE_LEFT):
			case (MOUSE_EVENT_MOVE_RIGHT):
			{
				mHidMouse[1] = mMousePosX;
				break;
			}
			default:
			{
				break;
			}
		}
	}
	mMousePosX = 0;
	mMousePosY = 0;
	mIsMouseDirty = false;
	return mHidMouse;
}



