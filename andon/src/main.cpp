#include "cooboc.h"
#include "gpio.h"
#include "stm32f10x_conf.h"
#include "hardware_serial.h"
#include "hardware_iic.h"
#include "keyboard.h"

extern "C" {
//usb
#include <usb_core.h>
#include <usb_init.h>

#include "hw_config.h"

}

__IO uint8_t PrevXferComplete = 1;


Keyboard keyboard;

void setup()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);


	Set_System();	
	USB_Interrupts_Config();
	Set_USBClock();
	USB_Init();


	Serial.begin(115200);
	Serial.println("program begin");
	
	//Iic1.begin(0x01);

	keyboard.setup();

}



unsigned long lastI2cTime = 0;
#define BMX055_ADDR   0x18
uint8_t i2cBuffer[8];
bool readBmx055Acc(uint8_t regAddr, int16_t *axis)
{
	bool ok = false;
	i2cBuffer[0] = regAddr;
	ok = Iic1.write(BMX055_ADDR, i2cBuffer, 1);
	if (ok)
	{
		ok = Iic1.read(BMX055_ADDR, i2cBuffer, 2);
		if (ok)
		{
			int8_t lsb = i2cBuffer[0];
			int8_t msb = i2cBuffer[1];
			*axis = ((int16_t)msb) << 8;
			*axis >>= 4;
			lsb &= 0x0F;
			*axis |= lsb;
		}
	}
	return ok;
}
bool readBmx055AccX(int16_t *x)
{
	return readBmx055Acc(0x02, x);
}
bool readBmx055AccY(int16_t *y)
{
	return readBmx055Acc(0x04, y);
}
bool readBmx055AccZ(int16_t *z)
{
	return readBmx055Acc(0x06, z);
}



void loop()
{
	keyboard.tick();
	/*
	int16_t x = 0;
	while (1)
	{
		
		bool ok = readBmx055AccX(&x);
		x /= 4;
		if (x > 127)
		{
			x = 127;
		}
		if (x < -127)
		{
			x = -127;
		}
		x = -x;
		Serial.println(x);
		Serial2.println(x);
		if (bDeviceState == CONFIGURED)
		{
			SendHidData((int8_t)x);
		} 
		delay(10);
	}

	Serial.println("dffsdafa");
	Serial2.println("dffsdafa");
	Serial2.println(x);
	delay(500);
	*/

	//Serial.println("hello world");
	//delay(20);

}
