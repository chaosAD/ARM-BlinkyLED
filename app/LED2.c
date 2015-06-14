#include "LED.h"
#include "Time.h"
#include "Button.h"

extern uint32_t counter;
extern uint32_t currentTime;

State blinkLED2(State state)
{
	static uint32_t previousTime = 0;
	static uint32_t dutyCycle = ONE_SEC;
	switch(state)
	{
		case INITIAL: turnOffLED(PORTG, LED4);
					  state = LED_OFF;
					  break;
		case LED_OFF: if(readUserButton())
							dutyCycle = ONE_HUND_MILISEC;
					  else
						  	dutyCycle  = FIVE_HUND_MILISEC;

					  if(isTimerExpire(dutyCycle, &previousTime))
					  {
							turnOnLED(PORTG, LED4);
							//previousTime = getCurrentTime();
							previousTime = currentTime;
							state = LED_ON;
							//currentTime = 0;
					  }
					  break;
		case LED_ON: if(readUserButton())
						dutyCycle = ONE_HUND_MILISEC;
					 else
						 dutyCycle  = FIVE_HUND_MILISEC;

					 if(isTimerExpire(dutyCycle, &previousTime))
					 {
							turnOffLED(PORTG, LED4);
							//previousTime = getCurrentTime();
							previousTime = currentTime;
							state = LED_OFF;
							//currentTime = 0;
					 }
		   	   	   	 break;
		default: state = INITIAL;
	}

	return state;
}
