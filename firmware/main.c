#include <libopencm3/stm32/rcc.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/hid.h>
#include <libopencm3/stm32/st_usbfs.h>
#include <libopencmsis/core_cm3.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/stm32/gpio.h>


#ifndef NULL
#define NULL 0
#endif

usbd_device *usbd_dev;

const struct usb_device_descriptor dev_descr = {
	.bLength = USB_DT_DEVICE_SIZE,
	.bDescriptorType = USB_DT_DEVICE,
	.bcdUSB = 0x0200,
	.bDeviceClass = 0,
	.bDeviceSubClass = 0,
	.bDeviceProtocol = 0,
	.bMaxPacketSize0 = 64,
	.idVendor = 0x8173,
	.idProduct = 0xA001,
	.bcdDevice = 0x0200,
	.iManufacturer = 1,
	.iProduct = 2,
	.iSerialNumber = 3,
	.bNumConfigurations = 1,
};

const struct usb_endpoint_descriptor hid_endpoint = {
	.bLength = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType = USB_DT_ENDPOINT,
	.bEndpointAddress = 0x81,
	.bmAttributes = USB_ENDPOINT_ATTR_INTERRUPT,
	.wMaxPacketSize = 17,
	.bInterval = 0x02,
};

static const uint8_t hid_report_descriptor[] = {


0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
0x09, 0x02,                    // USAGE (Mouse)
0xa1, 0x01,                    // COLLECTION (Application)

0x09, 0x01,                    //   USAGE (Pointer)
0xa1, 0x00,                    //   COLLECTION (Physical)
0x85, 0x03,						// report id 3
0x05, 0x09,                    //     USAGE_PAGE (Button)
0x19, 0x01,                    //     USAGE_MINIMUM (Button 1)
0x29, 0x03,                    //     USAGE_MAXIMUM (Button 3)
0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
0x95, 0x03,                    //     REPORT_COUNT (3)
0x75, 0x01,                    //     REPORT_SIZE (1)
0x81, 0x02,                    //     INPUT (Data,Var,Abs)
0x95, 0x01,                    //     REPORT_COUNT (1)
0x75, 0x05,                    //     REPORT_SIZE (5)
0x81, 0x03,                    //     INPUT (Cnst,Var,Abs)
0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
0x09, 0x30,                    //     USAGE (X)
0x09, 0x31,                    //     USAGE (Y)
0x15, 0x81,                    //     LOGICAL_MINIMUM (-127)
0x25, 0x7f,                    //     LOGICAL_MAXIMUM (127)
0x75, 0x08,                    //     REPORT_SIZE (8)
0x95, 0x02,                    //     REPORT_COUNT (2)
0x81, 0x06,                    //     INPUT (Data,Var,Rel)
0xc0,                          //   END_COLLECTION
0xc0,                           // END_COLLECTION


	 0x05, 0x01, // USAGE_PAGE (Generic Desktop)
	 0x09, 0x04, // USAGE (Joystick)

	 0xa1, 0x01, // COLLECTION (Application)
	 
		 0xa1, 0x00, // COLLECTION (Physical)
		 	0x85, 0x01, // report id 1
			 0x05, 0x09, // USAGE_PAGE (Button)
			 0x19, 0x01, // USAGE_MINIMUM (Button 1)
			 0x29, 0x08, // USAGE_MAXIMUM (Button 8)
			 0x15, 0x00, // LOGICAL_MINIMUM (0)
			 0x25, 0x01, // LOGICAL_MAXIMUM (1)
			 0x95, 0x08, // REPORT_COUNT (8)
			 0x75, 0x01, // REPORT_SIZE (1)
			 0x81, 0x02, // INPUT (Data,Var,Abs)

			 0x05, 0x01, // USAGE_PAGE (Generic Desktop)
			 0x09, 0x30, // USAGE (X)
			 0x09, 0x31, // USAGE (Y)
			 0x95, 0x02, // REPORT_COUNT
			 0x15, 0x00, // LOGICAL_MINIMUM (0)
			 0x26, 0xff, 0x0f, // LOGICAL_MAXIMUM
			 0x75, 0x10, // REPORT_SIZE
			 0x81, 0x82, // INPUT (Data,Var,Abs,Vol)

		 0xc0, // END_COLLECTION
	 0xc0, // END_COLLECTION

/*
	 0x05, 0x01, // USAGE_PAGE (Generic Desktop)
	 0x09, 0x04, // USAGE (Joystick)

	 0xa1, 0x01, // COLLECTION (Application)
		 0xa1, 0x00, // COLLECTION (Physical)
		 	 0x85, 0x02, // report id 2
			 0x05, 0x09, // USAGE_PAGE (Button)
			 0x19, 0x01, // USAGE_MINIMUM (Button 1)
			 0x29, 0x08, // USAGE_MAXIMUM (Button 8)
			 0x15, 0x00, // LOGICAL_MINIMUM (0)
			 0x25, 0x01, // LOGICAL_MAXIMUM (1)
			 0x95, 0x08, // REPORT_COUNT (8)
			 0x75, 0x01, // REPORT_SIZE (1)
			 0x81, 0x02, // INPUT (Data,Var,Abs)


		 0xc0, // END_COLLECTION
	 0xc0, // END_COLLECTION

*/


	 /*

	 0x05, 0x01, // USAGE_PAGE (Generic Desktop)
	 0x09, 0x04, // USAGE (Joystick)
 	 0xa1, 0x01, // COLLECTION (Application)
 	 
	 	0xa1, 0x00, // COLLECTION (Physical)
	 	0x85, 0x02, // report id 2
		 0x05, 0x09, // USAGE_PAGE (Button)
		 0x19, 0x01, // USAGE_MINIMUM (Button 1)
		 0x29, 0x08, // USAGE_MAXIMUM (Button 8)
		 0x15, 0x00, // LOGICAL_MINIMUM (0)
		 0x25, 0x01, // LOGICAL_MAXIMUM (1)
		 0x95, 0x08, // REPORT_COUNT (8)
		 0x75, 0x01, // REPORT_SIZE (1)
		 0x81, 0x02, // INPUT (Data,Var,Abs)
	 0xc0, // END_COLLECTION
 	0xc0, // END_COLLECTION
*/
};



static const struct {
	struct usb_hid_descriptor hid_descriptor;
	struct {
		uint8_t bReportDescriptorType;
		uint16_t wDescriptorLength;
	} __attribute__((packed)) hid_report;
} __attribute__((packed)) hid_function = {
	.hid_descriptor = {
		.bLength = sizeof(hid_function),
		.bDescriptorType = USB_DT_HID,
		.bcdHID = 0x0100,
		.bCountryCode = 0,
		.bNumDescriptors = 1,
	},
	.hid_report = {
		.bReportDescriptorType = USB_DT_REPORT,
		.wDescriptorLength = sizeof(hid_report_descriptor),
	}
};

const struct usb_interface_descriptor hid_iface = {
	.bLength = USB_DT_INTERFACE_SIZE,
	.bDescriptorType = USB_DT_INTERFACE,
	.bInterfaceNumber = 0,
	.bAlternateSetting = 0,
	.bNumEndpoints = 1,
	.bInterfaceClass = USB_CLASS_HID,
	.bInterfaceSubClass = 1, /* boot */
	.bInterfaceProtocol = 1, /* keyboard boot as keyboard */
	.iInterface = 0,

	.endpoint = &hid_endpoint,

	.extra = &hid_function,
	.extralen = sizeof(hid_function),
};

const struct usb_interface ifaces[] = {{
	.num_altsetting = 1,
	.altsetting = &hid_iface,
}};


const struct usb_config_descriptor config = {
	.bLength = USB_DT_CONFIGURATION_SIZE,
	.bDescriptorType = USB_DT_CONFIGURATION,
	.wTotalLength = 0,
	.bNumInterfaces = 1,
	.bConfigurationValue = 1,
	.iConfiguration = 0,
	.bmAttributes = 0xC0,
	.bMaxPower = 0x32,

	.interface = ifaces,
};

static const char *usb_strings[] = {
	"Cooboc",
	"H4K",
	"0x00011"
	/* This string is used by ST Microelectronics' DfuSe utility. */
	"@Internal Flash   /0x08000000/8*001Ka,56*001Kg",
};

uint8_t usbd_control_buffer[5*64];


uint32_t getChipId()
{
	return *(volatile uint8_t *)0x1FFFF7E8;
}

int hid_control_request(usbd_device *dev, struct usb_setup_data *req, uint8_t **buf, uint16_t *len,
			void (**complete)(usbd_device *dev, struct usb_setup_data *req))
{
	(void)complete;
	(void)dev;

	if((req->bmRequestType != 0x81) ||
	   (req->bRequest != USB_REQ_GET_DESCRIPTOR) ||
	   (req->wValue != 0x2200))
		return 0;

	/* Handle the HID report descriptor. */
	*buf = (uint8_t *)hid_report_descriptor;
	*len = sizeof(hid_report_descriptor);

	return USBD_REQ_HANDLED;
}

void hid_set_config(usbd_device *dev, uint16_t wValue)
{
	(void)wValue;

	usbd_ep_setup(dev, 0x81, USB_ENDPOINT_ATTR_INTERRUPT, 64, NULL);

	usbd_register_control_callback(
				dev,
				USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_INTERFACE,
				USB_REQ_TYPE_TYPE | USB_REQ_TYPE_RECIPIENT,
				hid_control_request);

	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8);
	/* SysTick interrupt every N clock pulses: set reload to N-1 */
	systick_set_reload(90000 - 1);	//100hz at 72M / 8
	systick_interrupt_enable();
	systick_counter_enable();
}


void usbSuspendCallback(void)
{
	//gpio_toggle(GPIOC, GPIO13);
}

void usb_wakeup_isr(void)
{
	exti_reset_request(EXTI18);
	rcc_clock_setup_in_hse_8mhz_out_72mhz();
	*USB_CNTR_REG &= ~USB_CNTR_FSUSP;
}


uint16_t value[8];
uint16_t vv;
int bb;
void sys_tick_handler(void)
{
	static uint8_t buf[1 + 16];

	vv += 10;
	if (vv > 0x0FFF)
	{
		vv = 0;
	}

	for (int i=0; i<8; ++i)
	{
		buf[i*2+2] = vv & 0xFF;	//Low
		buf[i*2+2+1] = vv >> 8; //high;
	}

	bb++;
	if (bb%2 == 0)
	{
		buf[0] = 3;	//report id 1 mouse
		//usbd_ep_write_packet(usbd_dev, 0x81, buf, 4);
	}
	else
	{
		int len;
		buf[0] = 1;//joystick
		len = usbd_ep_write_packet(usbd_dev, 0x81, buf, 6);
		if (len == 0)
		{
			//gpio_toggle(GPIOC, GPIO13);
		}
		buf[0] = 3;	//report id 1 mouse


		//len = usbd_ep_write_packet(usbd_dev, 0x81, buf, 4);

		//while (len == 0)
		{
			//len = usbd_ep_write_packet(usbd_dev, 0x81, buf, 4);
			//gpio_toggle(GPIOC, GPIO13);
		}
	}



	buf[0] = 0x01;	

	//usbd_ep_write_packet(usbd_dev, 0x81, buf, 6);


	if ((vv & (1<<5)) > 0)
	{
		//gpio_set(GPIOC, GPIO13);
	}
	else
	{
		//gpio_clear(GPIOC, GPIO13);
	}
}


void setupUsb();

void usbResetCallback()
{
	
	usbd_disconnect(usbd_dev, true);
	
	setupUsb();
}

volatile uint64_t sofCount;
volatile bool isSofBegin;

void usbSofCallback(void)
{
	sofCount = 0;
	isSofBegin = true;
	//gpio_toggle(GPIOC, GPIO13);
}

void setupUsb()
{
	nvic_enable_irq(NVIC_USB_WAKEUP_IRQ);

	gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO12);
	gpio_clear(GPIOA, GPIO12);
	for (unsigned int i = 0; i < 800000; i++)
		__asm__("nop");

	usbd_dev = usbd_init(&st_usbfs_v1_usb_driver, &dev_descr, &config, usb_strings, 2, usbd_control_buffer, sizeof(usbd_control_buffer));
	usbd_register_set_config_callback(usbd_dev, hid_set_config);
	usbd_register_suspend_callback(usbd_dev, usbSuspendCallback);
	usbd_register_reset_callback(usbd_dev, usbResetCallback);
	usbd_register_sof_callback(usbd_dev, usbSofCallback);

}



int main(void)
{
	usbd_dev = NULL;



	for (int i=0; i<8; ++i)
	{
		value[i] = 0;
	}
	rcc_clock_setup_in_hse_8mhz_out_72mhz();
	rcc_periph_clock_enable(RCC_GPIOA);

	rcc_periph_clock_enable(RCC_GPIOC);
	gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);
	gpio_set(GPIOC, GPIO13);

	setupUsb();
	sofCount = 0;
	isSofBegin = false;


	while (1)
	{
		if (isSofBegin)
		{
			sofCount ++;
		}
		usbd_poll(usbd_dev);

		if ((sofCount > 720000) && isSofBegin)
		{
			gpio_toggle(GPIOC, GPIO13);

			setupUsb();
			//_usbd_reset(usbd_dev);
			sofCount = 0;
			isSofBegin = false;
		}
	}


	return 0;
}