#include "cooboc.h"
#include "gpio.h"
#include "stm32f10x_conf.h"
#include "hardware_serial.h"
#include "hardware_can.h"

#include "devices/a7/aia7.h"
#include <line_parser.h>
#include "devices/gps/gps.h"

int a;
char buffer[5];

LineParser mlp;
Gps gps;

unsigned long lastPrintTime = 0UL;
bool pp = false;

void setup()
{
	pinMode(C13, OUTPUT);
	Serial.begin(115200);
	Serial2.begin(115200);
	Serial3.begin(9600);
	mlp.init();
	
	AiA7Begin(Serial2);

	a = 0;
	digitalWrite(C13, HIGH);

	Can.begin(CAN1);

	gps.init(Serial3);
	srand(3);
	lastPrintTime = 0;
	Serial.print("\r\n");
}




void loop()
{
	//Serial.print('.');
	AiA7Tick();
	gps.tick();
	while (Serial.available())
	{
		char c = Serial.read();
		mlp.feed(c);
		Serial.write(c);
	}

	if (mlp.hasData())
	{
		Serial.println();
		Serial2.print(mlp.getData());
		Serial2.print("\r\n");
	}

	if (getAiA7Status()==A7_STAUTS_IDLE && pp==false)
	{
		pp=true;
		Serial.print("A7 manufactore: ");
		Serial.println(ti.getManufacturer());
		Serial.print("A7 Model: ");
		Serial.println(ti.getModel());
		Serial.print("A7 Reversion: ");
		Serial.println(ti.getReversion());
		Serial.print("A7 Serial Number: ");
		Serial.println(ti.getSerialNumber());
		Serial.print("A7 CCID: ");
		Serial.println(ti.getCCID());
	}
}
