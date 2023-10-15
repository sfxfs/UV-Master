#ifndef _ROV_UTILS_OTHER_H_
#define _ROV_UTILS_OTHER_H_

#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt))) //限幅函数

void rov_delay(unsigned int ms);
void rov_delayMicroseconds(unsigned int us);

#endif