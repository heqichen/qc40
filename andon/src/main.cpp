#include "cooboc.h"
#include "gpio.h"
#include "stm32f10x_conf.h"
#include "hardware_serial.h"
#include "hardware_iic.h"
#include "keyboard.h"

#include "event_loop.h"
#include "hid.h"
#include "interpreter.h"



extern "C" {
//usb
#include <usb_core.h>
#include <usb_init.h>

#include "hw_config.h"

}

__IO uint8_t PrevXferComplete = 1;


#define PIN_USB_DISC A15

Keyboard keyboard;
EventLoop eventLoop;
Hid hid;
Interpreter interpreter;

void setup()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);

	pinMode(PIN_USB_DISC, OUTPUT);
	digitalWrite(PIN_USB_DISC, HIGH);
	
	Serial.begin(115200);
	Serial.println("program begin");
	delay(300);
	digitalWrite(PIN_USB_DISC, LOW);
	Iic1.begin(0x01);

	eventLoop.setup(&hid, &interpreter);
	keyboard.setup(&eventLoop);
	
	Set_System();	
	USB_Interrupts_Config();
	Set_USBClock();
	USB_Init();

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


unsigned long lastKeyboardTime = 0UL;
bool fff = false;


void keyboardSimTick()
{
	if (millis() - lastKeyboardTime < 1000)
	{
		return ;
	}

	Serial.println("emu");
	lastKeyboardTime = millis();
	uint8_t data[10];

	data[0] = 0x02;
	data[1] = 0x00;
	data[2] = 0x07;
	data[3] = 0x00;
	data[4] = 0x00;

	Serial.println(PrevXferComplete);
	if (bDeviceState == CONFIGURED)
	{
		sendKeyboardData(data, 5);
	}
	while (!PrevXferComplete)
	{

	}


	data[0] = 0x01;	//report id
	data[1] = 0x00;	//modification key
	data[2] = 0x00;	//constant
	data[3] = 0x00; //key1
	data[4] = 0x00; //key2
	data[5] = 0x00; //key3
	data[6] = 0x00; //key4
	data[7] = 0x00; //key5
	data[8] = 0x00; //key6
	if (fff)
	{
		data[3] = 0x0a;
		fff = false;
		Serial.println("g");
	}
	else
	{
		data[3] = 0;
		fff = true;
	}	

	if (bDeviceState == CONFIGURED)
	{
		sendKeyboardData(data, 9);
	}
	while (!PrevXferComplete)
	{

	}
	Serial.println(PrevXferComplete);
	
}

void loop()
{
	eventLoop.tick();
	keyboard.tick();

	//keyboardSimTick();
	
	int16_t x = 0;
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
	//Serial.println(x);
	if (bDeviceState == CONFIGURED)
	{
		//SendHidData((int8_t)x);
	} 
	delay(10);
	

	

	//Serial.println("hello world");
	//delay(20);

}
