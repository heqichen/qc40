#include "keyboard.h"

#include <gpio.h>
#include <hardware_serial.h>
#include <cooboc.h>

#define PIN_KB_EN	B0
#define PIN_KB_A0	B1
#define PIN_KB_A1	B2
#define PIN_KB_A2	B3

#define PIN_KB_C1	A0
#define PIN_KB_C2	A1
#define PIN_KB_C3	A2
#define PIN_KB_C4	A3
#define PIN_KB_C5	A4
#define PIN_KB_C6	A5
#define PIN_KB_C7	A6
#define PIN_KB_C8	A7


uint8_t PIN_KB_COLS[] = {PIN_KB_C1, PIN_KB_C2, PIN_KB_C3, PIN_KB_C4, PIN_KB_C5, PIN_KB_C6, PIN_KB_C7, PIN_KB_C8};

void Keyboard::setup(EventLoop *el)
{
	int i;
	mEventLoop = el;
	for (i=0; i<8; ++i)
	{
		pinMode(PIN_KB_COLS[i], INPUT);
	}


	pinMode(PIN_KB_EN, OUTPUT);
	pinMode(PIN_KB_A0, OUTPUT);
	pinMode(PIN_KB_A1, OUTPUT);
	pinMode(PIN_KB_A2, OUTPUT);

	digitalWrite(PIN_KB_EN, LOW);
	digitalWrite(PIN_KB_A0, LOW);
	digitalWrite(PIN_KB_A1, LOW);
	digitalWrite(PIN_KB_A2, LOW);

	mLastTickTime = 0;
	for (i=0; i<56; ++i)
	{
		mKeys[i].setup();
	}
}

void Keyboard::tick()
{
	if (millis() - mLastTickTime > 1)
	{
		mLastTickTime = millis();
		int x, y;
		digitalWrite(PIN_KB_EN, HIGH);
		for (y=0; y<7; ++y)
		{
			digitalWrite(PIN_KB_A0, (y&0x01)>0?HIGH:LOW);
			digitalWrite(PIN_KB_A1, ((y>>1)&0x01)>0?HIGH:LOW);
			digitalWrite(PIN_KB_A2, ((y>>2)&0x01)>0?HIGH:LOW);
			
			for(x=0; x<8; ++x)
			{
				mKeys[y*8 + x].tick(digitalRead(PIN_KB_COLS[x]));
				if (mKeys[y*8 + x].hasChanged())
				{
					if (mKeys[y*8+x].getNewValue() > 0)
					{
						mEventLoop->newEvent(EVENT_KEY_UP, y*8 + x);
					}
					else
					{
						mEventLoop->newEvent(EVENT_KEY_DOWN, y*8 + x);
					}
					
					/*
					Serial.print("Key: ");
					Serial.print(y*8+x);
					Serial.print(" has changed to ");
					Serial.println(mKeys[y*8+x].getNewValue());
					*/
				}
				//Serial.print(digitalRead(PIN_KB_COLS[x]));
			}
			//Serial.println("");
		}
		//Serial.println("");
	}
}