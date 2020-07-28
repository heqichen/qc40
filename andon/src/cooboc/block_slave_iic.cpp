#include "block_slave_iic.h"
#include "hardware_serial.h"

void onSlaveTxFrameStart(void * userData)
{
	((BlockSlaveIic*)userData)->onTxFrameStart();
}

void onSlaveRxFrameStart(void * userData)
{
	((BlockSlaveIic*)userData)->onRxFrameStart();
}

void onSlaveData(void * userData, uint8_t data)
{
	((BlockSlaveIic*)userData)->onData(data);
}

uint8_t slaveRequestData(void * userData)
{
	return ((BlockSlaveIic*)userData)->requestData();
}

void onSlaveAckFailure(void *userData)
{
	((BlockSlaveIic*)userData)->onAckFailure();
}


BlockSlaveIic::BlockSlaveIic(HardwareIic *iic)
	:	mIic	(iic),
		mStatus	(RECEIVING),
		mInputBlockPtr	(NULL),
		mOutputBlockPtr	(NULL),
		mBlockCursor	(0),
		mFrameOffset	(0),
		mMemroyCallback	(NULL)
{

}

void BlockSlaveIic::begin(uint8_t address, volatile uint8_t* inputPtr, volatile uint8_t *outputPtr)
{
	mInputBlockPtr = inputPtr;
	mOutputBlockPtr = outputPtr;
	mIic->begin(address);
	mIic->setInterruptService(onSlaveTxFrameStart, onSlaveRxFrameStart, onSlaveData, slaveRequestData, onSlaveAckFailure, this);

}

void BlockSlaveIic::setMemoryCallback(BlockSlaveIicCallback *memroyCallback)
{
	mMemroyCallback = memroyCallback;
}


void BlockSlaveIic::onTxFrameStart()
{
	mStatus = TRANSMITTING;
	mFrameOffset = 0;
}

void BlockSlaveIic::onRxFrameStart()
{
	mStatus = RECEIVING;
	mFrameOffset = 0;
}

void BlockSlaveIic::onData(uint8_t data)
{
	if (mFrameOffset == 0)
	{
		mBlockCursor = data;
	}
	else
	{
		mInputBlockPtr[mBlockCursor] = data;
		this->onReceived(mBlockCursor);
		mBlockCursor++;
	}
	mFrameOffset++;
}



uint8_t BlockSlaveIic::requestData()
{

	uint8_t data = mOutputBlockPtr[mBlockCursor];
	if (mFrameOffset > 0)
	{
		this->onSent(mBlockCursor-1);
	}
	mBlockCursor++;
	mFrameOffset++;
	return data;
}

void BlockSlaveIic::onAckFailure()
{
	if (mStatus == TRANSMITTING)
	{
		mBlockCursor --;
	}
}

void BlockSlaveIic::onReceived(uint8_t address)
{
	if (mMemroyCallback)
	{
		mMemroyCallback->onDataReceived(address);
	}
}

void BlockSlaveIic::onSent(uint8_t address)
{
	if (mMemroyCallback)
	{
		mMemroyCallback->onDataSent(address);
	}
}



