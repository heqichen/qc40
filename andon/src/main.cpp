#include "cooboc.h"
#include "gpio.h"
#include "stm32f10x_conf.h"
#include "hardware_serial.h"


extern "C" {
//usb
#include <usb_core.h>
#include <usb_init.h>

#include "hw_config.h"

}

__IO uint8_t PrevXferComplete = 1;

void setup()
{
	pinMode(C13, OUTPUT);
	Serial.begin(115200);
	Serial2.begin(115200);
	Serial3.begin(9600);


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
