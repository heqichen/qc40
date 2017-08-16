#ifndef __HARDWARE_SERIAL_H__
#define __HARDWARE_SERIAL_H__

#include "stm32f10x_usart.h"

#define DEC	10
#define HEX	16

#define HARDWARE_SERIAL_BUFFER_SIZE	128

class HardwareSerial
{
	public:
		HardwareSerial();
		void begin(int baudrate);
		void write(uint8_t ch);
		void println();

		void print(char ch);
		void println(char ch);
		void print(const char *str);
		void println(const char *str);
		void print(int d);
		void println(int d);
		void print(unsigned int d);
		void println(unsigned int d);
		void print(uint8_t d, int base);
		void print(unsigned long d);
		void println(unsigned long d);
		void print(double d);
		void println(double d);

		int available(void) const {return mRxBufferLength;};
		uint8_t read(void);

		inline void __rxService(uint8_t data);
		void __setUsart(USART_TypeDef *usartx);
	private:
		USART_TypeDef *mUsartx;
		uint8_t *mRxBuffer;
		int mRxBufferHeadIdx;
		int mRxBufferLength;
};


extern HardwareSerial Serial;
extern HardwareSerial Serial2;
extern HardwareSerial Serial3;


#endif
