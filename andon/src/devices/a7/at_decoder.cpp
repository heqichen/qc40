#include "at_decoder.h"
#include "hardware_serial.h"
#include "cooboc.h"

void AtDecoder::init()
{
	mLp.init();
	mEventNameBuffer = new char[AT_DECODER_EVENT_NAME_SIZE+1];
	mEventNameBuffer[0] = '\0';
	mDataPtr = mEventNameBuffer;
	mEventData = mEventNameBuffer;
	mResponseType = AT_RESPONSE_TYPE_NULL;
}

void AtDecoder::feed(char b)
{
	mLp.feed(b);
	if (mLp.hasData())
	{
		mDataPtr = mLp.getData();
		decodeData();
	}
}




void AtDecoder::decodeData()
{
	if (strncmp(mDataPtr, "+CME ERROR", 10) == 0)
	{
		mResponseType = AT_RESPONSE_TYPE_RESULT_ERROR;
		decodeEvent();
		return ;
	}

	if (strcmp(mDataPtr, "ERROR") == 0)
	{
		mResponseType = AT_RESPONSE_TYPE_RESULT_ERROR;
		mEventNameBuffer[0] = '\0';
		mEventData = mEventNameBuffer;
		return; 
	}

	if (strcmp(mDataPtr, "OK") == 0)
	{
		mResponseType = AT_RESPONSE_TYPE_RESULT_OK;
		mEventNameBuffer[0] = '\0';
		mEventData = mEventNameBuffer;
		return; 
	}

	if (strcmp(mDataPtr, "RING") == 0)
	{
		mResponseType = AT_RESPONSE_TYPE_RING;
		mEventNameBuffer[0] = '\0';
		mEventData = mEventNameBuffer;
		return ;
	}

	if (strncmp(mDataPtr, "^", 1) == 0)
	{
		mResponseType = AT_RESPONSE_TYPE_SYSTEM_EVENT;
		decodeEvent();
		return ;
	}

	if (strncmp(mDataPtr, "+", 1) == 0)
	{
		mResponseType = AT_RESPONSE_TYPE_NORMAL_EVENT;
		decodeEvent();
		return ;
	}

	mResponseType = AT_RESPONSE_TYPE_DATA;
	mEventNameBuffer[0] = '\0';
	mEventData = mEventNameBuffer;
}


void AtDecoder::decodeEvent()
{
	int i;
	i=0;
	while (i<31 && mDataPtr[i+1]!=':' && mDataPtr[i+1]!='\0')
	{
		mEventNameBuffer[i] = mDataPtr[i+1];
		++i;
	}
	mEventNameBuffer[i] = '\0';
	
	i++;
	while (mDataPtr[i]==' ')
	{
		++i;
	}
	mEventData = mDataPtr + i;


	Serial.print("event name: ");
	Serial.println(mEventNameBuffer);
	
	Serial.print("event value: ");
	Serial.println(mEventData);
}




void AtDecoder::clearResponse()
{
	mResponseType = AT_RESPONSE_TYPE_NULL;
	mEventNameBuffer[0] = '\0';
	mEventData = mEventNameBuffer;
}