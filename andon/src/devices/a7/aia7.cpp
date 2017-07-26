#include "aia7.h"
#include "cooboc.h"
#include "at_decoder.h"



#ifndef NULL
#define NULL 0
#endif


//http://www.electrodragon.com/w/GSM_GPRS_A6_Module


HardwareSerial *a7Serial;
int status;
int nextStatus;
AtDecoder ad;
typedef void (* A7TickWorker)(void);

void switchTo(int newStatus)
{
	nextStatus = newStatus;
}

void TaInfo::init()
{
	mManufacturer = new char[32];
	mModel = new char[32];
	mReversion = new char[32];
	mSerialNumber = new char[32];
	mCCID = new char[32];
	mManufacturer[0] = '\0';
	mModel[0] = '\0';
	mReversion[0] = '\0';
	mSerialNumber[0] = '\0';
	mCCID[0] = '\0';
}

void TaInfo::setManufacturer(const char * s)
{
	strcpy(mManufacturer, s);
}

void TaInfo::setModel(const char *s)
{
	strcpy(mModel, s);
}

void TaInfo::setReversion(const char *s)
{
	strcpy(mReversion, s);
}

void TaInfo::setSerialNumber(const char *s)
{
	strcpy(mSerialNumber, s);
}

void TaInfo::setCCID(const char *s)
{
	strcpy(mCCID, s);
}

TaInfo ti;

//==================== begin of configuring ===============
int runningCommand;

unsigned long commandStartTime = 0;
void configuringInit()
{
	Serial.println("entering configuring mode");
	a7Serial->print("AT\r\n");
	commandStartTime = millis();
	//Serial.println("AT command sent");
	runningCommand = 0;
}

void errorHandlingAndRunningCommand(int result, const char *cmd)
{
	if (result == AT_RESPONSE_TYPE_RESULT_OK)
	{
		a7Serial->print(cmd);
		a7Serial->print("\r\n");
		++runningCommand;
		return ;
	}
	if (result == AT_RESPONSE_TYPE_RESULT_ERROR)
	{
		switchTo(A7_STAUTS_ERROR);
	}
}

void configuringWorker()
{
	int result = ad.getResponseType();
	if (result != AT_RESPONSE_TYPE_NULL)
	{
		Serial.print("get response: ");
		Serial.println(result);
		
		switch (runningCommand)
		{
			case (0):
			{
				if ((result == AT_RESPONSE_TYPE_RESULT_OK) || (result == AT_RESPONSE_TYPE_RESULT_ERROR))
				{
					a7Serial->print("AT\r\n");
					runningCommand = 1;
				}
				break;
			}
			case (1):
			{
				errorHandlingAndRunningCommand(result, "ATE0");
				break;
			}
			case (2):
			{
				errorHandlingAndRunningCommand(result, "AT+CMEE=0");
				break;
			}
			case (3):
			{
				errorHandlingAndRunningCommand(result, "ATI");
				break;
			}
			case (4):
			{
				errorHandlingAndRunningCommand(result, "AT+GMI");
				break;
			}

			case (5):
			{
				if (result == AT_RESPONSE_TYPE_DATA)
				{
					ti.setManufacturer(ad.getRawData());
				}
				else
				{
					errorHandlingAndRunningCommand(result, "AT+GMM");
				}
				break;
			}
			case (6):
			{
				if (result == AT_RESPONSE_TYPE_DATA)
				{
					ti.setModel(ad.getRawData());
				}
				else
				{
					errorHandlingAndRunningCommand(result, "AT+GMR");
				}
				break;
			}
			case (7):
			{
				if (result == AT_RESPONSE_TYPE_DATA)
				{
					ti.setReversion(ad.getRawData());
				}
				else
				{
					errorHandlingAndRunningCommand(result, "AT+GSN");
				}
				break;
			}
			case (8):
			{
				if (result == AT_RESPONSE_TYPE_DATA)
				{
					ti.setSerialNumber(ad.getRawData());
				}
				else
				{
					if (result==AT_RESPONSE_TYPE_RESULT_OK || result==AT_RESPONSE_TYPE_RESULT_ERROR)
					{
						++runningCommand;
						a7Serial->print("AT+CCID\r\n");	//test if card inserted
					}
				}
				break;
			}
			case (9):
			{
				if (result == AT_RESPONSE_TYPE_NORMAL_EVENT )
				{
					if (strcmp(ad.getEventName(), "CCID") == 0)
					{
						ti.setCCID(ad.getEventData());
					}
				}
				else
				{
					errorHandlingAndRunningCommand(result, "AT+GPS=1");
				}
				break;
			}
			case (10):
			{
				errorHandlingAndRunningCommand(result, "AT+AGPS=1");
				break;
			}
			case (11):
			{
				errorHandlingAndRunningCommand(result, "AT+GPSRD=0");
				break;
			}
			default:
			{
				if (result == AT_RESPONSE_TYPE_RESULT_OK)
				{
					switchTo(A7_STAUTS_IDLE);
				}
				else
				{
					if (result == AT_RESPONSE_TYPE_RESULT_ERROR)
					{
						switchTo(A7_STAUTS_ERROR);
					}
				}
				break;
			}
		}
		ad.clearResponse();
	}
}

//==================== end of configuring ===============

//==================== begin of idle ===============

void idleInit()
{
	Serial.println("switch to idle work mode");
}

void idleWorker()
{
	int result = ad.getResponseType();
	{
		switch (result)
		{
			case (AT_RESPONSE_TYPE_RING):
			{
				switchTo(A7_STATUS_INCOMING_CALL);
				break;
			}
			default:
			{
				break;
			}
		}
	}
	ad.clearResponse();
	//Serial.println("done");
	//delay(1000);
}

//==================== end of idle ===============

//==================== end of incomingcall ===============
void incomingCallInit()
{
	a7Serial->print("ATH\r\n");
}

void  incomingCallWorker()
{
	int result = ad.getResponseType();
	if (result == AT_RESPONSE_TYPE_RESULT_OK)
	{
		switchTo(A7_STAUTS_IDLE);
		return ;
	}
	if (result == AT_RESPONSE_TYPE_RESULT_ERROR)
	{
		switchTo(A7_STAUTS_ERROR);
		return ;
	}

}

//==================== end of incomingcall ===============

//==================== begin of error ===============
void errorInit()
{
	Serial.println("entering erro work mode");
}

void errorWorker()
{

}
//==================== end of error ===============




A7TickWorker worker = NULL;




void doSwitchStatus()
{
	if (status == nextStatus)
	{
		return ;
	}

	switch(nextStatus)
	{
		case (A7_STAUTS_IDLE):
		{
			idleInit();
			worker = idleWorker;
			break;
		}
		case (A7_STAUTS_CONFIGURING):
		{
			configuringInit();
			worker = configuringWorker;
			break;
		}
		case (A7_STATUS_INCOMING_CALL):
		{
			incomingCallInit();
			worker = incomingCallWorker;
			break;
		}
		case (A7_STAUTS_ERROR):
		{
			errorInit();
			worker = errorWorker;
			Serial.println("set to error work");
			break;
		}
		default:
		{

			break;
		}
	}
	status = nextStatus;
}

void AiA7Begin(HardwareSerial &s)
{
	a7Serial = &s;
	ad.init();
	ti.init();
	status = -1;
	nextStatus = -1;
	switchTo(A7_STAUTS_CONFIGURING);
}

void AiA7Tick(void)
{
	doSwitchStatus();
	while (a7Serial->available())
	{
		char t = a7Serial->read();
	 	ad.feed(t);
	 	if (t=='\n' || t=='\r')
	 	{
	 		break;
	 	}
	}
	worker();
}

int getAiA7Status(void)
{
	return status;
}

