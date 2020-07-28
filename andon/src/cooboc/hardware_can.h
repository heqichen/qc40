#ifndef __HARDWARE_CAN_H__
#define __HARDWARE_CAN_H__

#include "stm32f10x_can.h"
#include "stm32f10x_rcc.h"

#define HARDWARE_CAN_RX_BUFFER_SIZE 20

typedef struct
{
	uint32_t stdId;
	uint32_t extId;
	bool isExtendedId;
	bool isDataMessage;	//false = remote transmission request
	uint8_t dataLength;
	uint8_t data[8];
} CanRxMessage;

class HardwareCan
{
	public:
		void begin(CAN_TypeDef* CANx);

		inline void __rx0InterruptService(CAN_TypeDef* CANx);

		bool send(uint32_t id, bool isExtendedId, uint8_t *data, int length);
		int available(void) const {return mRxBufferLength;};
		CanRxMessage read();
	private:
		CAN_TypeDef *mCanx;
		CanTxMsg mTxMessage;
		CanRxMsg *mRxMessageBuffer;
		int mRxBufferHeadIdx;
		int mRxBufferLength;
};

extern HardwareCan Can;

#endif

