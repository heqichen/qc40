#include "interpreter.h"

#include <hardware_serial.h>
#include "keymap.h"

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
	Serial.print(simKc, 16);
	Serial.println("");
	
}

