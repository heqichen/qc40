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
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
  pinMode(A10, OUTPUT);
  pinMode(B11, OUTPUT);
  digitalWrite(A10, LOW);
  digitalWrite(B11, HIGH);
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
      for (int i=0; i<100; ++i)
      {
        Joystick_Send(i);
        delay(10);
      }
    } 
  }
/*

  digitalWrite(B11, HIGH);
  delay(500);
  digitalWrite(B11, LOW);
  delay(500);
  */
}
