
#include "cooboc.h"

#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "hardware_serial.h"
#include "hardware_iic.h"

#include <stm32f10x_rcc.h>


int errno;

void memset(void *dest, uint8_t content, int size)
{
	uint8_t *ptr = (uint8_t*)dest;
	while (size--)
	{
		*ptr++ = content;
	}
}

void memcpy(void *dest, const void *src, int size)
{
	uint8_t *dp = (uint8_t*)dest;
	const uint8_t *sp = (uint8_t*)src;
	while (size--)
	{
		*dp++ = *sp++;
	}
}

void strcpy(char *dest, const char *src)
{
   char *save = dest;
   while((*dest++) = (*src++));
}

int strcmp(const char* str1, const char* str2)
{
	while (((*str1)==(*str2)) && (*str1)!='\0')
	{
		++str1;
		++str2;
	}

	return ((*str1)-(*str2));
}

int strncmp(const char* str1, const char* str2, int n)
{
	if (n < 1)
	{
		return 0;
	}
	while (((*str1)==(*str2)) && (*str1)!='\0' && n>0)
	{
		++str1;
		++str2;
		--n;
	}
	if (n > 0)
	{
		return ((*str1)-(*str2));
	}
	else
	{
		return 0;
	}
	
}

unsigned long millis()
{
	return __coobocMs;
}

unsigned long micros()
{
	return 0;
}

void delay(unsigned long ms)
{
	unsigned long startTime = __coobocMs;
	while (__coobocMs-startTime < ms)
	{}
}

void delayMicroseconds(unsigned long ms)
{
	
}

void itoa(int d, char *dest)
{
	int32_t first = 0;
	int32_t last = 0;
	char tmp;
	if (d == 0)
	{
		dest[0] = '0';
		dest[1] = '\0';
		return ;
	}

	if (d == 1<<31)
	{

		dest[0] = '-';
		dest[1] = '2';
		dest[2] = '1';
		dest[3] = '4';
		dest[4] = '7';
		dest[5] = '4';
		dest[6] = '8';
		dest[7] = '3';
		dest[8] = '6';
		dest[9] = '4';
		dest[10] = '8';
		dest[11] = '\0';
		return ;
	}

	if (d < 0)
	{
		dest[0] = '-';
		first = 1;
		last = 1;
		d = -d;
	}
	while (d > 0)
	{
		dest[last] = '0' + d % 10;
		d /= 10;
		++last;
	}
	dest[last] = '\0';
	--last;
	while (last > first)
	{
		tmp = dest[last];
		dest[last] = dest[first];
		dest[first] = tmp;

		--last;
		++first;
	}
}


void itoa(unsigned int d, char *dest)
{
	int32_t first = 0;
	int32_t last = 0;
	char tmp;
	if (d == 0)
	{
		dest[0] = '0';
		dest[1] = '\0';
		return ;
	}

	while (d > 0)
	{
		dest[last] = '0' + d % 10;
		d /= 10;
		++last;
	}
	dest[last] = '\0';
	--last;
	while (last > first)
	{
		tmp = dest[last];
		dest[last] = dest[first];
		dest[first] = tmp;

		--last;
		++first;
	}
}

void itoa(unsigned long d, char *dest)
{
	int32_t first = 0;
	int32_t last = 0;
	char tmp;
	if (d == 0)
	{
		dest[0] = '0';
		dest[1] = '\0';
		return ;
	}

	while (d > 0)
	{
		dest[last] = '0' + d % 10;
		d /= 10;
		++last;
	}
	dest[last] = '\0';
	--last;
	while (last > first)
	{
		tmp = dest[last];
		dest[last] = dest[first];
		dest[first] = tmp;

		--last;
		++first;
	}
}

void initSysClock(void)
{
	//stm32 Clock diagram see http://embedded-lab.com/blog/stm32-internals/
	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_ON);
	ErrorStatus HSEStartupStatus;
	HSEStartupStatus = RCC_WaitForHSEStartUp();
	if (HSEStartupStatus == SUCCESS)
	{
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		FLASH_SetLatency(FLASH_Latency_2);
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		RCC_PCLK2Config(RCC_HCLK_Div1);
		RCC_PCLK1Config(RCC_HCLK_Div2);
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);
		RCC_PLLCmd(ENABLE);
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET)
		{}
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		while(RCC_GetSYSCLKSource()!=0x08)
		{}
	}
	else
	{
		errno = COOBOC_ERR_HSE_STARTUP_ERROR;
	}

}


void initSysTick()
{
	if (SysTick_Config(SystemCoreClock/1000))
	{
		errno = COOBOC_ERR_SYSTICK_CONFIG;
	}
}



void (*timer2Callback)(void) = NULL;


void setTimer2Callback(void(*callback)(void))
{
	timer2Callback = callback;
}


void writeInt32ToStream(uint8_t *dest, int32_t data)
{
	int i;
	for (i=0; i<4; ++i)
	{
		uint8_t v = data & 0xFF;
		dest[i] = v;
		data >>= 8;
	}
}

void writeInt16ToStream(uint8_t *dest, int16_t data)
{
	uint8_t v = data & 0xFF;
	dest[0] = v;
	data >>= 8;
	v = data & 0xFF;
	dest[1] = v;
}

#ifdef __cplusplus
extern "C" {
#endif

void timer2InterruptService()
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		if (timer2Callback != NULL)
		{
			timer2Callback();
		}
	}
}


int main(void)
{
	errno = COOBOC_ERR_NOERR;
	__coobocMs = 0UL;

	timer2Callback = NULL;

	initSysClock();
	initSysTick();

	Serial.__setUsart(USART1);
	Serial2.__setUsart(USART2);
	Serial3.__setUsart(USART3);

	Iic1.__setPort(I2C1_B8_B9);
	Iic2.__setPort(I2C2_B10_B11);

	setup();
	while (true)
	{
		loop();
	}
}

#ifdef __cplusplus
}
#endif


