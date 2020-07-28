#ifndef __LINE_PARSER_H__
#define __LINE_PARSER_H__


#define LINE_PARSER_BUFFER_SIZE 256




class LineParser
{
	public:
		void init();
		void feed(char b);
		bool hasData() const {return mHasData;}
		char *getData() {mHasData=false; return mOutputBuffer;}
	private:
		char *mBuffer;
		char *mOutputBuffer;
		bool mIsSynced;
		int mContentLength;
		bool mHasData;


};

#endif

