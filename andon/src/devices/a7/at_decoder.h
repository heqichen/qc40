#ifndef __AT_DECODER_H__
#define __AT_DECODER_H__

#include <line_parser.h>

#define AT_RESPONSE_TYPE_NULL			0x00
#define AT_RESPONSE_TYPE_SYSTEM_EVENT	0x01
#define AT_RESPONSE_TYPE_NORMAL_EVENT	0x02
#define AT_RESPONSE_TYPE_RESULT_OK		0x03
#define AT_RESPONSE_TYPE_RESULT_ERROR	0x04
#define AT_RESPONSE_TYPE_DATA			0X05
#define AT_RESPONSE_TYPE_RING			0x06

#define AT_DECODER_EVENT_NAME_SIZE 16

class AtDecoder
{
	public:
		void init();
		void feed(char b);

		int getResponseType() const {return mResponseType;}
		void clearResponse();
		const char *getRawData() const {return mDataPtr;}
		const char *getEventName() const {return mEventNameBuffer;}
		const char *getEventData() const {return mEventData;}
	private:
		LineParser mLp;
		char *mEventNameBuffer;
		char *mDataPtr;
		char *mEventData;
		int mResponseType;

		void decodeData();
		void decodeEvent();
};

#endif

