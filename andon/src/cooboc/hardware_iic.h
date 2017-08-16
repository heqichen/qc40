#ifndef __HARDWARE_I2C_H__
#define __HARDWARE_I2C_H__

#include <stdint.h>
#include <stm32f10x_i2c.h>

#define I2C1_B8_B9		0
#define I2C2_B10_B11	1


#ifdef __cplusplus
extern "C" {
#endif
void I2C1EventInturruptService();
void I2C1ErrorInturruptService();
void I2C2EventInturruptService();
void I2C2ErrorInturruptService();
#ifdef __cplusplus
}
#endif

#ifndef NULL
#define NULL 0
#endif

typedef void (*InterruptServiceOnSlaveTxFrameStart)(void *);
typedef void (*InterruptServiceOnSlaveRxFrameStart)(void *);
typedef void (*InterruptServiceOnSlaveData)(void *, uint8_t);
typedef uint8_t (*InterruptServiceSlaveRequestData)(void *);
typedef void (*InterruptServiceOnSlaveAckFailure)(void *);



class HardwareIic
{
	public:
		HardwareIic(int iicPort);
		bool begin(uint8_t address);
		void setInterruptService(InterruptServiceOnSlaveTxFrameStart, InterruptServiceOnSlaveRxFrameStart, InterruptServiceOnSlaveData, InterruptServiceSlaveRequestData, InterruptServiceOnSlaveAckFailure, void *);
		bool write(uint8_t address, uint8_t *buf, int length);
		bool read(uint8_t address, uint8_t *buf, int length);
	private:

		int mIicPort;
		int mTransCount;
		I2C_TypeDef* mI2Cx;
		volatile enum WorkMode
		{
			IDLE,							//0
			SLAVE_RECEIVER,					//1
			SLAVE_TRANSMITTER,				//2
			MASTER_TRANSMITTING_ADDRESSING,	//3
			MASTER_TRANSMITTING,			//4
			MASTER_TRANSMITTING_STOPPING,	//5
			MASTER_RECEIVING_ADDRESS,		//6
			MASTER_RECEIVING,				//7
			MASTER_RECEIVING_STOPPING		//8
		} mWorkMode;

		static bool mIsI2C1Initialized;
		static bool mIsI2C2Initialized;
		InterruptServiceOnSlaveTxFrameStart mInterruptServiceOnSlaveTxFrameStart;
		InterruptServiceOnSlaveRxFrameStart mInterruptServiceOnSlaveRxFrameStart;
		InterruptServiceOnSlaveData mInterruptServiceOnSlaveData;
		InterruptServiceSlaveRequestData mInterruptServiceSlaveRequestData;
		InterruptServiceOnSlaveAckFailure mInterruptServiceOnSlaveAckFailure;
		void * mInterruptServiceData;

		void initializeI2C2(uint8_t address);
		void initializeI2C1(uint8_t address);
		void initializeB10B11();
		void initializeB8B9();
		void eventService();
		void errorService();

		uint32_t eventServiceOnIdle(uint32_t flag);
		uint32_t eventServiceOnSlave(uint32_t flag);
		uint32_t eventServiceOnMasterTransmitting(uint32_t flag);
		uint32_t eventServiceOnMasterReceiving(uint32_t flag);

		friend void I2C1EventInturruptService();
		friend void I2C1ErrorInturruptService();
		friend void I2C2EventInturruptService();
		friend void I2C2ErrorInturruptService();

		uint8_t mTransBusAddr;
		uint8_t *mTransData;
		int mTransLength;
		volatile bool mTransGood;
		
};

extern HardwareIic Iic1;
extern HardwareIic Iic2;

#endif