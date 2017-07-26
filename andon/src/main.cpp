#include "cooboc.h"
#include "gpio.h"
#include "stm32f10x_conf.h"
#include "hardware_serial.h"


void setup()
{
	pinMode(C13, OUTPUT);
	Serial.begin(115200);
	Serial2.begin(115200);
	Serial3.begin(9600);

}


void loop()
{
	digitalWrite(C13, LOW);
	Serial.println("hello wrld\r\n");
	delay(500);
	digitalWrite(C13, HIGH);
	delay(500);
}
