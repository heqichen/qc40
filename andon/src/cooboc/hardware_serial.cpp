
#include "hardware_serial.h"

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"

#include "gpio.h"
#include "cooboc.h"
#include <math.h>
//#include <cstdlib>

char PRINT_CHARACTER[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

#ifdef __cplusplus
extern "C" {
#endif

void USART1InterruptService(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		uint8_t data = USART_ReceiveData(USART1);
		Serial.__rxService(data);
	}
}

void USART2InterruptService(void)
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		uint8_t data = USART_ReceiveData(USART2);
		Serial2.__rxService(data);
	}
}

void USART3InterruptService(void)
{
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		uint8_t data = USART_ReceiveData(USART3);
		Serial3.__rxService(data);
	}
}


#ifdef __cplusplus
}
#endif



HardwareSerial::HardwareSerial()
{

}

void HardwareSerial::begin(int baudrate)
{
	USART_InitTypeDef USART_InitStructure;
	
	if (mUsartx == USART1)
	{
		mRxBuffer = new uint8_t[HARDWARE_SERIAL_BUFFER_SIZE];
		mRxBufferHeadIdx = 0;
		mRxBufferLength = 0;


		/*

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
		
		pinMode(A9, GPIO_MUX_PUSH_PULL);
		pinMode(A10, INPUT_FLOATING);
		*/
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOB, ENABLE);
		
		pinMode(B6, GPIO_MUX_PUSH_PULL);
		pinMode(B7, INPUT_FLOATING);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
		GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);



		NVIC_InitTypeDef NVIC_InitStructure;

		/* Enable the USARTz Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		USART_InitStructure.USART_BaudRate = baudrate;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(USART1, &USART_InitStructure);

		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

		USART_Cmd(USART1, ENABLE);
	}
	else if (mUsartx == USART2)
	{
		mRxBuffer = new uint8_t[HARDWARE_SERIAL_BUFFER_SIZE];
		mRxBufferHeadIdx = 0;
		mRxBufferLength = 0;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		
		pinMode(A2, GPIO_MUX_PUSH_PULL);
		pinMode(A3, INPUT_FLOATING);
		
		NVIC_InitTypeDef NVIC_InitStructure;

		/* Enable the USARTz Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);


		USART_InitStructure.USART_BaudRate = baudrate;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(USART2, &USART_InitStructure);

		USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

		USART_Cmd(USART2, ENABLE);
	}
	else if (mUsartx == USART3)
	{
		mRxBuffer = new uint8_t[HARDWARE_SERIAL_BUFFER_SIZE];
		mRxBufferHeadIdx = 0;
		mRxBufferLength = 0;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		
		pinMode(B10, GPIO_MUX_PUSH_PULL);
		pinMode(B11, INPUT_FLOATING);
		
		NVIC_InitTypeDef NVIC_InitStructure;

		/* Enable the USARTz Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);


		USART_InitStructure.USART_BaudRate = baudrate;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(USART3, &USART_InitStructure);

		USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

		USART_Cmd(USART3, ENABLE);
	}
}




void HardwareSerial::write(uint8_t ch)
{
	USART_SendData(mUsartx, ch);
	while (USART_GetFlagStatus(mUsartx, USART_FLAG_TC) == RESET)
	{
	}
}

void HardwareSerial::println(void)
{
	this->print('\r');
	this->print('\n');
}

void HardwareSerial::print(char ch)
{
	this->write((uint8_t)ch);
}

void HardwareSerial::println(char ch)
{
	this->print(ch);
	this->println();
}

void HardwareSerial::print(const char *str)
{
	while (*str != '\0')
	{
		this->print(*str);
		++str;
	}
}

void HardwareSerial::println(const char *str)
{
	this->print(str);
	this->println();
}

void HardwareSerial::print(int d)
{
	char buffer[16];
	itoa(d, buffer);
	this->print(buffer);
}


void HardwareSerial::println(int d)
{
	this->print(d);
	this->println();
}

void HardwareSerial::print(unsigned int d)
{
	char buffer[16];
	itoa(d, buffer);
	this->print(buffer);
}


void HardwareSerial::println(unsigned int d)
{
	this->print(d);
	this->println();
}
	
void HardwareSerial::print(uint8_t d, int base)
{
	switch (base)
	{
		case (DEC):
		{
			print(d);
			break;
		}
		case (HEX):
		{
			print(PRINT_CHARACTER[(d>>4) & 0x0F]);
			print(PRINT_CHARACTER[d & 0x0F]);
			break;
		}
		default:
		{
			break;
		}
	}
}


void HardwareSerial::print(unsigned long d)
{
	char buffer[16];
	itoa(d, buffer);
	this->print(buffer);
}

void HardwareSerial::println(unsigned long d)
{
	this->print(d);
	this->println();
}

void HardwareSerial::print(double d)
{
	char buffer[24];
	int len = 0;
	if (d < 0)
	{
		buffer[len] = '-';
		d = -d;
		len++;
	}

	unsigned long integer = floor(d);
	itoa(integer, buffer+len);
	while (buffer[len] != '\0')
	{
		++len;
	}
	d -= integer;
	buffer[len] = '.';
	len++;
	for (int i=0; i<3; ++i)
	{
		d *= 10;
		integer = floor(d);
		d -= integer;
		buffer[len] = integer + '0';
		++len;
	}
	buffer[len] = '\0';
	this->print(buffer);
}

void HardwareSerial::println(double d)
{
	this->print(d);
	this->println();
}

inline void HardwareSerial::__rxService(uint8_t data)
{
	//looks good
	if (mRxBufferLength < HARDWARE_SERIAL_BUFFER_SIZE)
	{
		mRxBuffer[(mRxBufferHeadIdx + mRxBufferLength) % HARDWARE_SERIAL_BUFFER_SIZE] = data;
		++mRxBufferLength;
		if (mRxBufferLength > HARDWARE_SERIAL_BUFFER_SIZE)
		{
			mRxBufferLength -= HARDWARE_SERIAL_BUFFER_SIZE;
		}
	}
	else
	{
		mRxBuffer[mRxBufferHeadIdx] = data;
		++mRxBufferHeadIdx;
		mRxBufferHeadIdx %= HARDWARE_SERIAL_BUFFER_SIZE;
	}
}

void HardwareSerial::__setUsart(USART_TypeDef *usartx)
{
	mUsartx = usartx;
}

uint8_t HardwareSerial::read(void)
{
	uint8_t ret = 0;
	if (mRxBufferLength > 0)
	{
		ret = mRxBuffer[mRxBufferHeadIdx];
		++mRxBufferHeadIdx;
		mRxBufferHeadIdx %= HARDWARE_SERIAL_BUFFER_SIZE;
		--mRxBufferLength;
	}
	return ret;
}

HardwareSerial Serial;
HardwareSerial Serial2;
HardwareSerial Serial3;