#include "LED.h"
#include "Time.h"

extern uint32_t counter;
extern uint32_t currentTime;

State blinkLED1(State state)
{
	static uint32_t previousTime = 0;
	switch(state)
	{
		case INITIAL: turnOffLED(PORTG, LED3);
					  state = LED_OFF;
					  break;
		case LED_OFF: if(isTimerExpire(ONE_HUND_TWENTY_MILISEC, &previousTime))
					  {
							turnOnLED(PORTG, LED3);
							//previousTime = getCurrentTime();
							previousTime = currentTime;
							state = LED_ON;
					  }
					  break;
		case LED_ON: if(isTimerExpire(ONE_HUND_TWENTY_MILISEC, &previousTime))
					 {
							turnOffLED(PORTG, LED3);
							//previousTime = getCurrentTime();
							previousTime = currentTime;
							state = LED_OFF;
					 }
		   	   	   	 break;
		default: state = INITIAL;
	}

	return state;
}
