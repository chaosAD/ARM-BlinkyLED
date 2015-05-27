#include "stm32f4xx_hal.h"
#include "LED.h"
#include "Time.h"

State blinkLED1(State state)
{
	static uint32_t previousTime = 0;
	switch(state)
	{
		case INITIAL: turnOffLED(LED3, PORT_G);
					  state = LED_OFF;
					  break;
		case LED_OFF: if(isTimerExpire(ONE_HUND_TWENTY_MILISEC, previousTime))
					  {
							turnOnLED(LED3, PORT_G);
							previousTime = getCurrentTime();
							state = LED_ON;
					  }
					  break;
		case LED_ON: if(isTimerExpire(ONE_HUND_TWENTY_MILISEC, previousTime))
					 {
							turnOffLED(LED3, PORT_G);
							previousTime = getCurrentTime();
							state = LED_OFF;
					 }
		   	   	   	 break;
		default: state = INITIAL;
	}

	return state;
}
