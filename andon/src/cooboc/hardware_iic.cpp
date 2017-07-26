#include "hardware_iic.h"
#include "hardware_serial.h"

#include <cooboc.h>

#include <stm32f10x_rcc.h>


bool HardwareIic::mIsI2C1Initialized = false;
bool HardwareIic::mIsI2C2Initialized = false;

void I2C2EventInturruptService()
{
	Iic2.eventService();
}
void I2C2ErrorInturruptService()
{
	Iic2.errorService();
}

HardwareIic::HardwareIic(int iicPort)
	:	mIicPort	(iicPort),
		mWorkMode	(IDLE),
		mInterruptServiceOnSlaveTxFrameStart	(NULL),
		mInterruptServiceOnSlaveRxFrameStart	(NULL),
		mInterruptServiceOnSlaveData			(NULL),
		mInterruptServiceSlaveRequestData		(NULL),
		mInterruptServiceOnSlaveAckFailure		(NULL),
		mInterruptServiceData 	(NULL)

{
	
}


bool HardwareIic::begin(uint8_t address)
{
	switch (mIicPort)
	{
		case (I2C2_B10_B11):
		{
			if (HardwareIic::mIsI2C2Initialized)
			{
				return false;
			}
			this->initializeB10B11();
			this->initializeI2C2(address);
			mI2Cx = I2C2;
			break;
		}
		default:
		{
			return false;
		}
	}

	return true;

}

void HardwareIic::setInterruptService(InterruptServiceOnSlaveTxFrameStart interruptServiceOnSlaveTxFrameStart, InterruptServiceOnSlaveRxFrameStart interruptServiceOnSlaveRxFrameStart, InterruptServiceOnSlaveData interruptServiceOnSlaveData, InterruptServiceSlaveRequestData interruptServiceSlaveRequestData, InterruptServiceOnSlaveAckFailure interruptServiceOnSlaveAckFailure, void *userData)
{
	mInterruptServiceOnSlaveTxFrameStart = interruptServiceOnSlaveTxFrameStart;
	mInterruptServiceOnSlaveRxFrameStart = interruptServiceOnSlaveRxFrameStart;
	mInterruptServiceOnSlaveData = interruptServiceOnSlaveData;
	mInterruptServiceSlaveRequestData = interruptServiceSlaveRequestData;
	mInterruptServiceOnSlaveAckFailure = interruptServiceOnSlaveAckFailure;
	mInterruptServiceData = userData;
}

void HardwareIic::initializeB10B11()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void HardwareIic::initializeI2C2(uint8_t address)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	I2C_InitTypeDef I2C_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = I2C2_EV_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = I2C2_ER_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);

	I2C_DeInit(I2C2);
	I2C_InitStructure.I2C_ClockSpeed = 400000;
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = address<<1;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init(I2C2, &I2C_InitStructure);

	I2C_ITConfig(I2C2, I2C_IT_BUF | I2C_IT_EVT | I2C_IT_ERR, ENABLE);
	
	I2C_Cmd(I2C2, ENABLE);
}

//SR2
#define IIC_FLAG_DUALF		(uint32_t)_BV(23)
#define IIC_FLAG_SMBHOST	(uint32_t)_BV(22)
#define IIC_FLAG_SMBDE_FAULT	(uint32_t)_BV(21)
#define IIC_FLAG_GEN_CALL	(uint32_t)_BV(20)
#define IIC_FLAG_TRA		(uint32_t)_BV(18)
#define IIC_FLAG_BUSY		(uint32_t)_BV(17)
#define IIC_FLAG_MSL		(uint32_t)_BV(16)

//SR1
#define IIC_FLAG_SMB_ALERT	(uint32_t)_BV(15)
#define IIC_FLAG_TIMEOUT	(uint32_t)_BV(14)
#define IIC_FLAG_PEC_ERR	(uint32_t)_BV(12)
#define IIC_FLAG_OVR		(uint32_t)_BV(11)
#define IIC_FLAG_AF			(uint32_t)_BV(10)
#define IIC_FLAG_ARLO		(uint32_t)_BV(9)
#define IIC_FLAG_BERR		(uint32_t)_BV(8)
#define IIC_FLAG_TxE		(uint32_t)_BV(7)
#define IIC_FLAG_RxNE		(uint32_t)_BV(6)
#define IIC_FLAG_STOPF		(uint32_t)_BV(4)
#define IIC_FLAG_ADD10		(uint32_t)_BV(3)
#define IIC_FLAG_BTF		(uint32_t)_BV(2)
#define IIC_FLAG_ADDR		(uint32_t)_BV(1)
#define IIC_FLAG_SB			(uint32_t)_BV(0)




void captureError(uint32_t flag)
{
	/*
	char *flags[24];
	int i;
	flags[23] = (char *)"IIC_FLAG_DUALF";
	flags[22] = (char *)"IIC_FLAG_SMBHOST";
	flags[21] = (char *)"IIC_FLAG_SMBDE_FAULT";
	flags[20] = (char *)"IIC_FLAG_GEN_CALL";
	flags[19] = (char *)"SR2[3]";
	flags[18] = (char *)"IIC_FLAG_TRA";
	flags[17] = (char *)"IIC_FLAG_BUSY";
	flags[16] = (char *)"IIC_FLAG_MSL";
	flags[15] = (char *)"IIC_FLAG_SMB_ALERT";
	flags[14] = (char *)"IIC_FLAG_TIMEOUT";
	flags[13] = (char *)"SR1[13]";
	flags[12] = (char *)"IIC_FLAG_PEC_ERR";
	flags[11] = (char *)"IIC_FLAG_OVR";
	flags[10] = (char *)"IIC_FLAG_AF";
	flags[9] = (char *)"IIC_FLAG_ARLO";
	flags[8] = (char *)"IIC_FLAG_BERR";
	flags[7] = (char *)"IIC_FLAG_TxE";
	flags[6] = (char *)"IIC_FLAG_RxNE";
	flags[5] = (char *)"SR1[5]";
	flags[4] = (char *)"IIC_FLAG_STOPF";
	flags[3] = (char *)"IIC_FLAG_ADD10";
	flags[2] = (char *)"IIC_FLAG_BTF";
	flags[1] = (char *)"IIC_FLAG_ADDR";
	flags[0] = (char *)"IIC_FLAG_SB";

	*/

	Serial.println(flag);
	while (true) ;
}

void HardwareIic::eventService()
{
	/*
	uint16_t cr1 = I2C_ReadRegister(mI2Cx, I2C_Register_CR1);
	uint32_t sr1 = I2C_ReadRegister(mI2Cx, I2C_Register_SR1);
	uint32_t sr2 = I2C_ReadRegister(mI2Cx, I2C_Register_SR2);
	*/
	uint16_t cr1 = mI2Cx->CR1;
	uint32_t sr1 = mI2Cx->SR1;//I2C_ReadRegister(mI2Cx, I2C_Register_SR1);
	uint32_t sr2 = mI2Cx->SR2;//I2C_ReadRegister(mI2Cx, I2C_Register_SR2);

	uint32_t flag = (sr2<<16 | sr1) & 0x00FFFFFF;
	
	if (flag & IIC_FLAG_ADDR)
	{
		if (flag & IIC_FLAG_TRA)
		{
			mWorkMode = SLAVE_TRANSMITTER;
			if (mInterruptServiceOnSlaveTxFrameStart)
			{
				mInterruptServiceOnSlaveTxFrameStart(mInterruptServiceData);
			}
		}
		else
		{
			mWorkMode = SLAVE_RECEIVER;
			if (mInterruptServiceOnSlaveRxFrameStart)
			{
				mInterruptServiceOnSlaveRxFrameStart(mInterruptServiceData);
			}
		}
		flag ^= IIC_FLAG_ADDR;
	}

	if (flag & IIC_FLAG_TRA)
	{
		flag ^= IIC_FLAG_TRA;
	}


	if (flag & IIC_FLAG_RxNE)
	{
		uint8_t data = mI2Cx->DR;
		if (mWorkMode==SLAVE_RECEIVER)
		{
			if (mInterruptServiceOnSlaveData)
			{
				mInterruptServiceOnSlaveData(mInterruptServiceData, data);
			}
		}
		flag ^= IIC_FLAG_RxNE;
	}


	if (flag & IIC_FLAG_TxE)
	{
		if (mInterruptServiceSlaveRequestData)
		{
			mI2Cx->DR = mInterruptServiceSlaveRequestData(mInterruptServiceData);
		}
		else
		{
			mI2Cx->DR = 0;
		}
		
		flag ^= IIC_FLAG_TxE;
	}

	/*
	if (flag & IIC_FLAG_AF)
	{
		mI2Cx->SR1 = 0;
		flag ^= IIC_FLAG_AF;
	}
	*/

	if (flag & IIC_FLAG_STOPF)
	{
		mI2Cx->CR1 = cr1;
		mWorkMode = IDLE;
		flag ^= IIC_FLAG_STOPF;
		//rx frame end
		//end
	}

	if (flag & IIC_FLAG_BUSY)
	{
		//end
		flag ^= IIC_FLAG_BUSY;
	}

	if (flag != 0)
	{
		Serial.println("something forgot handle");
		//TODO need hardrest
		//step1. deinit i2c
		//step2. set sda and scl to gpio
		//step3. set sda and scl high
		//step4. init i2c
		captureError(flag);
	}
}

void HardwareIic::errorService()
{
	uint16_t cr1 = mI2Cx->CR1;	//just read it
	uint32_t sr1 = mI2Cx->SR1;
	uint32_t sr2 = mI2Cx->SR2;

	uint32_t flag = (sr2<<16 | sr1) & 0x00FFFFFF;

	if (flag == (IIC_FLAG_AF | IIC_FLAG_BUSY | IIC_FLAG_TRA))
	{
		// nack of transmitter frame
		mI2Cx->SR1 = 0;
		flag = 0;
		if (mInterruptServiceOnSlaveAckFailure)
		{
			mInterruptServiceOnSlaveAckFailure(mInterruptServiceData);
		}
	}

	if (flag != 0)
	{
		Serial.println("IIC Error!!");

		captureError(flag);	
	}

	
}

HardwareIic Iic2(I2C2_B10_B11);