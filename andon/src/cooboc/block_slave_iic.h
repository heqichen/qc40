#ifndef __BLOCK_SLAVE_IIC_H__
#define __BLOCK_SLAVE_IIC_H__

#include "hardware_iic.h"


#ifndef NULL
#define NULL 0
#endif

void onSlaveTxFrameStart(void *);
void onSlaveRxFrameStart(void *);
void onSlaveData(void *, uint8_t);
uint8_t slaveRequestData(void *);
void onSlaveAckFailure(void *);


class BlockSlaveIicCallback
{
	public:
		virtual void onDataReceived(uint8_t address) = 0;
		virtual void onDataSent(uint8_t address) = 0;
};


class BlockSlaveIic
{
	public:
		BlockSlaveIic(HardwareIic *iic);
		void begin(uint8_t address, volatile uint8_t* inputPtr, volatile uint8_t *outputPtr);
		void setMemoryCallback(BlockSlaveIicCallback *memroyCallback);
	private:
		HardwareIic *mIic;
		enum Status
		{
			RECEIVING,
			TRANSMITTING
		} mStatus;
		volatile uint8_t *mInputBlockPtr;
		volatile uint8_t *mOutputBlockPtr;
		volatile uint8_t mBlockCursor;
		int mFrameOffset;
		BlockSlaveIicCallback *mMemroyCallback;

		void onTxFrameStart();
		void onRxFrameStart();
		void onData(uint8_t);
		uint8_t requestData();
		void onAckFailure();

		void onReceived(uint8_t address);
		void onSent(uint8_t address);

		friend void onSlaveTxFrameStart(void *);
		friend void onSlaveRxFrameStart(void *);
		friend void onSlaveData(void *, uint8_t);
		friend uint8_t slaveRequestData(void *);
		friend void onSlaveAckFailure(void *);

};



#endif


