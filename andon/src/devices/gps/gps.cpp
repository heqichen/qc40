#include "gps.h"
#include <cooboc.h>

//http://www.gpsinformation.org/dale/nmea.htm
//http://aprs.gids.nl/nmea/#gga

void Gps::init(HardwareSerial &s)
{
	mSerial = &s;
	mlp.init();
}




void Gps::tick()
{
	while (mSerial->available())
	{
		char t = mSerial->read();
		mlp.feed(t);
		if ((t=='\r') || (t=='\n'))
		{
			break;
		}
	}

	if (mlp.hasData())
	{
		char *sentence = mlp.getData();
		if (strncmp(sentence, "$GPGGA,", 7) == 0)
		{
			decodeGpgga(sentence);
			return ;
		}

		Serial.print("UNKOWN GPS sentence: ");
		Serial.println(sentence);
	}
}

void Gps::decodeGpgga(char *s)
{
	int idx = 7;
	
	Serial.println(s);
}