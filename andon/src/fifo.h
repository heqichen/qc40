#ifndef __FIFO_H__
#define __FIFO_H__

#include <stdint.h>

class Fifo
{
	public:
		void setup(int size);
		void push(uint32_t vv);
		int size() const {return mBufferLength;};
		uint32_t pop(void);
	private:
		uint32_t *mBuffer;
		int mBufferSize;
		int mHeadIdx;
		int mTailIdx;
		int mBufferLength;
};



#endif 

