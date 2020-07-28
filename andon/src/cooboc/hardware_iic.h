#ifndef __HARDWARE_I2C_H__
#define __HARDWARE_I2C_H__

#include <stdint.h>
#include <stm32f10x_i2c.h>

#define I2C2_B10_B11	0

#ifdef __cplusplus
extern "C" {
#endif

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
	private:

		int mIicPort;
		I2C_TypeDef* mI2Cx;
		enum WorkMode
		{
			IDLE,
			SLAVE_RECEIVER,
			SLAVE_TRANSMITTER
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
		void initializeB10B11();
		void eventService();
		void errorService();

		friend void I2C2EventInturruptService();
		friend void I2C2ErrorInturruptService();
		
};

extern HardwareIic Iic2;

#endif