#include "cooboc.h"
#include "gpio.h"
#include "stm32f10x_conf.h"
#include "hardware_serial.h"
#include "hardware_can.h"

extern "C" 
{
#include <hw_config.h>
}

__IO uint8_t PrevXferComplete = 1;

void setup()
{
	pinMode(C13, OUTPUT);
	Serial.begin(115200);
}




void loop()
{
  Set_System();
  
  USB_Interrupts_Config();
  
  Set_USBClock();
  
  USB_Init();
  
  while (1)
  {
    if (bDeviceState == CONFIGURED)
    {
      if ((JoyState() != 0) && (PrevXferComplete))
      {
        Joystick_Send(JoyState());
      }
    } 
  }
}
