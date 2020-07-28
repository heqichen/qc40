#ifndef __AI_A7_H__
#define __AI_A7_H__

#include <hardware_serial.h>


#define A7_STAUTS_POWEROFF		0x00
#define A7_STAUTS_POWERUP		0x01
#define A7_STAUTS_INITIALIZING	0x02
#define A7_STAUTS_CONFIGURING	0x03
#define A7_STAUTS_IDLE			0x04
#define A7_STAUTS_SMS			0x05
#define A7_STAUTS_TCP			0x06
#define A7_STATUS_INCOMING_CALL	0x07				
#define A7_STAUTS_ERROR			0xF1


class TaInfo
{
	public:
		void init();
		void setManufacturer(const char * s);
		void setModel(const char *s);
		void setReversion(const char *s);
		void setSerialNumber(const char *s);
		void setCCID(const char *s);
		char* getManufacturer() {return mManufacturer;}
		char *getModel() {return mModel;}
		char *getReversion() {return mReversion;}
		char *getSerialNumber() {return mSerialNumber;}
		char *getCCID() {return mCCID;}
	private:
		char *mManufacturer;
		char *mModel;
		char *mReversion;
		char *mSerialNumber;
		char *mCCID;
};


void AiA7Begin(HardwareSerial &s);
void AiA7Tick(void);
int getAiA7Status(void);

extern TaInfo ti;

#endif


