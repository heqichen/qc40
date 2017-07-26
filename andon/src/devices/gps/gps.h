#ifndef __GPS_H__
#define __GPS_H__

#include <hardware_serial.h>
#include <line_parser.h>

class Gps
{
	public:
		void init(HardwareSerial &s);
		void tick();
	private:
		HardwareSerial *mSerial;
		LineParser mlp;

		int readField(const char *sentence, char *buffer);

		void decodeGpgga(char *s);

};


#endif

