#include "fifo.h"


void Fifo::setup(int size)
{
	mBufferSize = size;
	mBuffer = new uint32_t[size];
	mHeadIdx = 0;
	mTailIdx = 0;
	mBufferLength = 0;
}

void Fifo::push(uint32_t vv)
{
	//TODO need turn off irq
	if (mBufferLength < mBufferSize)
	{
		mBuffer[mTailIdx] = vv;
		mTailIdx ++;
		mTailIdx %= mBufferSize;
		mBufferLength++;
	}
}

uint32_t Fifo::pop(void)
{
	if (mBufferLength > 0)
	{
		uint32_t ret = mBuffer[mHeadIdx];
		mHeadIdx++;
		mHeadIdx %= mBufferSize;
		mBufferLength=mBufferLength-1;
		return ret;
	}
	else
	{
		return 0;
	}
}