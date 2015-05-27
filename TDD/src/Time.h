#ifndef Time_H
#define Time_H

#include "Utils.h"

#define ONE_SEC					1000
#define ONE_HUND_TWENTY_MILISEC	120
#define ONE_HUND_MILISEC		100
#define TWO_HUND_MILISEC		200

uint32_t getCurrentTime();
void delay(uint32_t delayCycle);
uint32_t isTimerExpire(uint32_t delayCycle, uint32_t previousTime);

#endif // Time_H
