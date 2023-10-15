#ifndef _UTILS_OTHER_H_
#define _UTILS_OTHER_H_

#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt))) //限幅函数

void uvm_delay(unsigned int ms);
void uvm_delayMicroseconds(unsigned int us);

#endif