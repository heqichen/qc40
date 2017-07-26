#include "gps.h"


void Gps::decodeGpgga(char *s)
{
	int idx = 7;
	char buffer[64];
	int nRead;

	Serial.println("\n\n");
	Serial.println(s);

	nRead = this->readField(s+idx, buffer);
	idx += nRead;
	Serial.print("read time: ");
	Serial.print(buffer);
	Serial.print("\tidx: ");
	Serial.println(idx);

	nRead = this->readField(s+idx, buffer);
	idx += nRead;
	Serial.print("Latitude: ");
	Serial.print(buffer);
	Serial.print("\tidx: ");
	Serial.println(idx);

	nRead = this->readField(s+idx, buffer);
	idx += nRead;
	Serial.print("direction: ");
	Serial.print(buffer);
	Serial.print("\tidx: ");
	Serial.println(idx);

	nRead = this->readField(s+idx, buffer);
	idx += nRead;
	Serial.print("Longitude: ");
	Serial.print(buffer);
	Serial.print("\tidx: ");
	Serial.println(idx);

	nRead = this->readField(s+idx, buffer);
	idx += nRead;
	Serial.print("direction: ");
	Serial.print(buffer);
	Serial.print("\tidx: ");
	Serial.println(idx);

	nRead = this->readField(s+idx, buffer);
	idx += nRead;
	Serial.print("Fix Quality: ");
	Serial.print(buffer);
	Serial.print("\tidx: ");
	Serial.println(idx);

	nRead = this->readField(s+idx, buffer);
	idx += nRead;
	Serial.print("Number of Satellites: ");
	Serial.print(buffer);
	Serial.print("\tidx: ");
	Serial.println(idx);

	nRead = this->readField(s+idx, buffer);
	idx += nRead;
	Serial.print("Horizontal Dilution of Precision: ");
	Serial.print(buffer);
	Serial.print("\tidx: ");
	Serial.println(idx);

	nRead = this->readField(s+idx, buffer);
	idx += nRead;
	Serial.print("Altitude: ");
	Serial.print(buffer);
	Serial.print("\tidx: ");
	Serial.println(idx);

	nRead = this->readField(s+idx, buffer);
	idx += nRead;
	Serial.print("Altitude Unite: ");
	Serial.print(buffer);
	Serial.print("\tidx: ");
	Serial.println(idx);

	nRead = this->readField(s+idx, buffer);
	idx += nRead;
	Serial.print("Height of geoid above WGS84 ellipsoid: ");
	Serial.print(buffer);
	Serial.print("\tidx: ");
	Serial.println(idx);

}