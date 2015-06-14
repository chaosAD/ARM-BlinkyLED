#include "LED.h"
#include "Time.h"
#include "Button.h"

extern uint32_t counter;
extern uint32_t currentTime;

State blinkLED3(State state)
{
	static uint32_t previousTime = 0;
	static uint32_t blinkTime = 0;
	switch(state)
	{
		case INITIAL: turnOffLED(PORTB, LED5);
					  if(readUserButton())
						  state = LED_OFF;
					  else
						  state = INITIAL;
					  break;
		case LED_OFF: if(isTimerExpire(FIVE_HUND_MILISEC, &previousTime))
					  {
							turnOnLED(PORTB, LED5);
							//previousTime = getCurrentTime();
							previousTime = currentTime;
							state = LED_ON;
					  }
					  break;
		case LED_ON: if(blinkTime == 5)
					 {
						state = WAIT_BUTTON_RELEASE;
						blinkTime = 0;
					 }
					 else
					 {
						 if(isTimerExpire(FIVE_HUND_MILISEC, &previousTime))
						 {
							 turnOffLED(PORTB, LED5);
							 //previousTime = getCurrentTime();
							 previousTime = currentTime;
							 state = LED_OFF;
							 blinkTime++;
						 }
					 }
		   	   	   	 break;
		case WAIT_BUTTON_RELEASE: turnOffLED(PORTB, LED5);
								  if(!readUserButton())
									state = INITIAL;
								  else
									state = WAIT_BUTTON_RELEASE;
								  break;
		default: state = INITIAL;
	}

	return state;
}
