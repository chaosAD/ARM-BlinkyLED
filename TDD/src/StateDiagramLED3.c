#include "Utils.h"
#include "StateDiagramLED3.h"
#include "Time.h"
#include "Button.h"

State blinkLED3(State state)
{
	static uint32_t previousTime = 0;
	static uint32_t blinkTime = 0;
	switch(state)
	{
		case INITIAL: turnOffLED(LED3, PORT_B);
					  if(readUserButton())
						  state = LED_OFF;
					  else
						  state = INITIAL;
					  break;
		case LED_OFF: if(isTimerExpire(ONE_SEC, previousTime))
					  {
							turnOnLED(LED3, PORT_B);
							previousTime = getCurrentTime();
							state = LED_ON;
					  }
					  break;
		case LED_ON: if(blinkTime == 5)
					 {
						state = WAIT_FOR_RELEASE;
						blinkTime = 0;
					 }
					 else
					 {
						 if(isTimerExpire(ONE_SEC, previousTime))
						 {
							 turnOffLED(LED3, PORT_B);
							 previousTime = getCurrentTime();
							 state = LED_OFF;
							 blinkTime++;
						 }
					 }
		   	   	   	 break;
		case WAIT_FOR_RELEASE: if(!readUserButton())
									state = WAIT_FOR_RELEASE;
							   else
								   state = INITIAL;
		default: state = INITIAL;
	}

	return state;
}
