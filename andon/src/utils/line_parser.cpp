#include "line_parser.h"
#include "hardware_serial.h"
#include "cooboc.h"


void LineParser::init()
{
	mIsSynced = true;
	mContentLength = 0;
	mHasData = false;
	
	mBuffer = new char[LINE_PARSER_BUFFER_SIZE];
	mOutputBuffer = new char[LINE_PARSER_BUFFER_SIZE+1];	// +1 for ending char '\0'

}

void LineParser::feed(char b)
{
	if (mIsSynced)
	{
		if (mContentLength == 0)
		{
			if (b=='\r' || b=='\n' || b==' ' || b=='\t')
			{
				//trim leading spaces
				return ;
			}
		}

		if (mContentLength >= LINE_PARSER_BUFFER_SIZE)
		{
			mIsSynced = false;
			mContentLength = 0;
		}
		else
		{
			if (b=='\r' || b=='\n')
			{
				//line end
				memcpy(mOutputBuffer, mBuffer, mContentLength);
				mOutputBuffer[mContentLength] = '\0';
				mHasData = true;

				//Serial.print("LP DBG]");
				//Serial.println(mOutputBuffer);

				mIsSynced = true;
				mContentLength = 0;
			}
			else
			{
				mBuffer[mContentLength] = b;
				++mContentLength;		
			}

		}


	}
	else
	{
		if (b=='\r' || b=='\n')
		{
			mIsSynced = true;
			mContentLength = 0;
		}
	}
}


