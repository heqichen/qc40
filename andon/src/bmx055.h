#ifndef __BMX055_H__
#define __BMX055_H__


#include <stdint.h>

bool readBmx055AccX(int16_t *x);
bool readBmx055AccY(int16_t *y);
bool readBmx055AccZ(int16_t *z);



#endif



