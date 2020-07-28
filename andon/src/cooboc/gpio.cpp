#include "gpio.h"

#include "stm32f10x_adc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

const uint32_t RCC_PERIPHERAL_ADDRESS[7] = {RCC_APB2Periph_GPIOA, RCC_APB2Periph_GPIOB, RCC_APB2Periph_GPIOC, RCC_APB2Periph_GPIOD, RCC_APB2Periph_GPIOE, RCC_APB2Periph_GPIOF, RCC_APB2Periph_GPIOG};
GPIO_TypeDef *GPIO_BASE[7] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG};

//internal function

uint16_t mapPin2Id(int pin)
{
	return ((uint16_t)(1<<(pin%16)));
}

void initialADC1(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_ADC1, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);

	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_Init(ADC1, &ADC_InitStructure);
	
	ADC_Cmd(ADC1, ENABLE);
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1))
	{}
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
	{}

	ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
}

//global function
void pinMode(int pin, int mode)
{
	int portId = pin / 16;
	GPIO_InitTypeDef gpio;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_PERIPHERAL_ADDRESS[portId], ENABLE);
	gpio.GPIO_Pin = mapPin2Id(pin);
	gpio.GPIO_Mode = (GPIOMode_TypeDef)mode;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIO_BASE[portId], &gpio);

	if (mode == INPUT_ANALOG)
	{
		initialADC1();
	}
}

int analogRead(int pin)
{
	switch (pin)
	{
		case A0:
		{
			ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
			break;
		}
		case A1:
		{
			ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);
			break;
		}
		case A2:
		{
			ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_55Cycles5);
			break;
		}
		case A3:
		{
			ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 1, ADC_SampleTime_55Cycles5);
			break;
		}
		case A4:
		{
			ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_55Cycles5);
			break;
		}
		case A5:
		{
			ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_55Cycles5);
			break;
		}
		case A6:
		{
			ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime_55Cycles5);
			break;
		}
		case A7:
		{
			ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 1, ADC_SampleTime_55Cycles5);
			break;
		}
		case B0:
		{
			ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_55Cycles5);
			break;
		}
		case B1:
		{
			ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1, ADC_SampleTime_55Cycles5);
			break;
		}
		case C0:
		{
			ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_55Cycles5);
			break;
		}
		case C1:
		{
			ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 1, ADC_SampleTime_55Cycles5);
			break;
		}
		case C2:
		{
			ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 1, ADC_SampleTime_55Cycles5);
			break;
		}
		case C3:
		{
			ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 1, ADC_SampleTime_55Cycles5);
			break;
		}
		case C4:
		{
			ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 1, ADC_SampleTime_55Cycles5);
			break;
		}
		case C5:
		{
			ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 1, ADC_SampleTime_55Cycles5);
			break;
		}

	}
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
	{}
	int ret = ADC_GetConversionValue(ADC1);
	
	

	return ret;
}


void digitalWrite(int pin, int value)
{
	if (value == LOW)
	{
		GPIO_ResetBits(GPIO_BASE[pin/16], mapPin2Id(pin));
	}
	else
	{
		GPIO_SetBits(GPIO_BASE[pin/16], mapPin2Id(pin));
	}
}

int digitalRead(int pin)
{
	if (GPIO_ReadInputDataBit(GPIO_BASE[pin/16], mapPin2Id(pin)) == 0)
	{
		return LOW;
	}
	else
	{
		return HIGH;
	}
}
