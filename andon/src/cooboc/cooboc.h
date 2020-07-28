#ifndef __COOBOC_H__
#define __COOBOC_H__

#include "gpio.h"
#include "stdlib.h"

#ifndef NULL
#define NULL 0
#endif



#define _BV(bit) 	(1 << (bit)) 

#define B0000	0x00
#define B0001	0x01
#define B0010	0x02
#define B0011	0x03
#define B0100	0x04
#define B0101	0x05
#define B0110	0x06
#define B0111	0x07
#define B1000	0x08
#define B1001	0x09
#define B1010	0x0A
#define B1011	0x0B
#define B1100	0x0C
#define B1101	0x0D
#define B1110	0x0E
#define B1111	0x0F

#define B111111	0x3F

#define COOBOC_ERR_NOERR	0
#define COOBOC_ERR_SYSTICK_CONFIG	1
#define COOBOC_ERR_HSE_STARTUP_ERROR 2

extern int errno;

void memset(void *dest, uint8_t content, int size);
void memcpy(void *dest, const void *src, int size);
void strcpy(char *dest, const char *src);
int strcmp(const char* str1, const char* str2);
int strncmp(const char* str1, const char* str2, int n);

unsigned long millis();
unsigned long micros();
void delay(unsigned long ms);
void delayMicroseconds(unsigned long ms);

void itoa(int d, char *dest);
void itoa(unsigned int d, char *dest);
void itoa(unsigned long d, char *dest);

void setup();
void loop();

void setTimer2Callback(void(*callback)(void));

void writeInt32ToStream(uint8_t *dest, int32_t data);
void writeInt16ToStream(uint8_t *dest, int16_t data);


#endif
