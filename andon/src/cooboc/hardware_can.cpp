#include "cooboc.h"
#include "hardware_can.h"
#include "hardware_serial.h"
#include "gpio.h"
#include "stm32f10x_can.h"


#ifdef __cplusplus
extern "C" {
#endif

void CAN1Rx0InterruptService(void)
{
	Can.__rx0InterruptService(CAN1);
}


#ifdef __cplusplus
}
#endif

void HardwareCan::begin(CAN_TypeDef* CANx)
{
	if (CANx == CAN1)
	{
		//cool

		mCanx = CAN1;
		mRxMessageBuffer = new CanRxMsg[HARDWARE_CAN_RX_BUFFER_SIZE];
		pinMode(A12, GPIO_Mode_AF_PP);
		pinMode(A11, GPIO_Mode_IPU);
		//GPIO_PinRemapConfig(GPIO_Remap2_CAN1 , ENABLE);

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);



		CAN_DeInit(CAN1);

		CAN_InitTypeDef CAN_InitStructure;
		CAN_StructInit(&CAN_InitStructure);
		CAN_InitStructure.CAN_TTCM = DISABLE;		//time triggered communication mode
		CAN_InitStructure.CAN_ABOM = DISABLE;		//auto bus-off management, turn off bus when TCE or RCE greater than a threshold
		CAN_InitStructure.CAN_AWUM = DISABLE;		//auto wake up manage, if disable, must wake up by api
		CAN_InitStructure.CAN_NART = ENABLE;		//no automatic retransmissioin, dialbe = auto
		CAN_InitStructure.CAN_RFLM = DISABLE;		//receive FIFO locked mode, override overflow message
		CAN_InitStructure.CAN_TXFP = ENABLE;		//tx fifo piroity, enabled = by add seq, disable = by id,
		CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;	//normal
		//CAN_InitStructure.CAN_Mode = CAN_Mode_LoopBack;	//normal
		CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;  	//max changable tq	, if at 500K 1tq is enough
		CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;	//pbs1
		CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;	//pbs2
		//500Kbps
		CAN_InitStructure.CAN_Prescaler =12;		// 36 / 6 / (SS+PBS1+PBS2) = 36/ 6/ (1+3+2)
		CAN_Init(CANx, &CAN_InitStructure);


		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);


		CAN_FilterInitTypeDef  CAN_FilterInitStructure;
		CAN_FilterInitStructure.CAN_FilterNumber=0;
		CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;
		CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;
		CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;
		CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
		CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;
		CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;  
		CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;
		CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
		CAN_FilterInit(&CAN_FilterInitStructure);

		CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);	//fifo message pending

		mRxBufferHeadIdx = 0;
		mRxBufferLength = 0;
	}
}

bool HardwareCan::send(uint32_t id, bool isExtendedId, uint8_t *data, int length)
{
	int i;
	uint32_t tmeMask = 0;
	uint32_t txokMask = 0;
	if (isExtendedId)
	{
		mTxMessage.StdId = id & 0x000007FF;
		mTxMessage.ExtId = 0;
		mTxMessage.IDE = CAN_Id_Standard;
	}
	else
	{
		mTxMessage.StdId = 0;
		mTxMessage.ExtId = id & 0x1FFFFFFF;
		mTxMessage.IDE = CAN_Id_Extended;
	}
	mTxMessage.RTR = CAN_RTR_Data;
	if (length > 8)
	{
		length = 8;
	}
	mTxMessage.DLC = length;
	for (i=0; i<length; ++i)
	{
		mTxMessage.Data[i] = data[i];
	}
	uint8_t mailboxId = CAN_Transmit(mCanx, &mTxMessage);
	//RM0008 P665 page.
	if (mailboxId > 2)
	{
		return false;
	}
	//can use CAN_TransmitStatus(), but for performance sack
	switch (mailboxId)
	{
		case (0):
		{
			tmeMask = CAN_TSR_TME0;
			txokMask = CAN_TSR_TXOK0;
			break;
		}
		case (1):
		{
			tmeMask = CAN_TSR_TME1;
			txokMask = CAN_TSR_TXOK1;
			break;
		}
		case (2):
		{
			tmeMask = CAN_TSR_TME2;
			txokMask = CAN_TSR_TXOK2;
			break;
		}
		default:
		{
			break;
		}
	}
	while (((mCanx->TSR) & tmeMask) == 0)
	{
		//wait for transmit
	}
	return (((mCanx->TSR)&txokMask) > 0);
}

CanRxMessage HardwareCan::read()
{
	CanRxMessage ret;
	memset(&ret, 0, sizeof(ret));
	if (mRxBufferLength > 0)
	{

		ret.stdId = mRxMessageBuffer[mRxBufferHeadIdx].StdId;
		ret.extId = mRxMessageBuffer[mRxBufferHeadIdx].ExtId;
		ret.isExtendedId = (mRxMessageBuffer[mRxBufferHeadIdx].IDE == CAN_Id_Extended);
		ret.isDataMessage = (mRxMessageBuffer[mRxBufferHeadIdx].RTR == CAN_RTR_Data);
		ret.dataLength = mRxMessageBuffer[mRxBufferHeadIdx].DLC;
		memcpy((void*)ret.data, (void*)mRxMessageBuffer[mRxBufferHeadIdx].Data, ret.dataLength);

		++mRxBufferHeadIdx;
		mRxBufferHeadIdx %= HARDWARE_CAN_RX_BUFFER_SIZE;
		--mRxBufferLength;
	}

	return ret;
}

inline void HardwareCan::__rx0InterruptService(CAN_TypeDef* CANx)
{
	int rxPtr = 0;
	if (CANx == mCanx) // i.e CAN1
	{
		//looks good
		if (mRxBufferLength < HARDWARE_CAN_RX_BUFFER_SIZE)
		{
			rxPtr = (mRxBufferHeadIdx+mRxBufferLength) % HARDWARE_CAN_RX_BUFFER_SIZE;
			++mRxBufferLength;
			if (mRxBufferLength > HARDWARE_CAN_RX_BUFFER_SIZE)
			{
				mRxBufferLength -= HARDWARE_CAN_RX_BUFFER_SIZE;
			}
		}
		else
		{
			rxPtr = mRxBufferHeadIdx;
			++mRxBufferHeadIdx;
			mRxBufferHeadIdx %= HARDWARE_CAN_RX_BUFFER_SIZE;
		}
		CAN_Receive(CAN1, CAN_FIFO0, mRxMessageBuffer + rxPtr);
	}
}

HardwareCan Can;


