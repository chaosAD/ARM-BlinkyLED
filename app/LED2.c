#include "stm32f4xx_hal.h"
#include "LED.h"
#include "Time.h"
#include "Button.h"

State blinkLED2(State state)
{
	static uint32_t previousTime = 0;
	static uint32_t dutyCycle = ONE_SEC;
	switch(state)
	{
		case INITIAL: turnOffLED(LED4, PORT_G);
					  state = LED_OFF;
					  break;
		case LED_OFF: if(readUserButton())
							dutyCycle = ONE_HUND_MILISEC;
					  else
						  	dutyCycle  = ONE_SEC;

					  if(isTimerExpire(dutyCycle, previousTime))
					  {
							turnOnLED(LED4, PORT_G);
							previousTime = getCurrentTime();
							state = LED_ON;
							//currentTime = 0;
					  }
					  break;
		case LED_ON: if(readUserButton())
						dutyCycle = ONE_HUND_MILISEC;
					 else
						 dutyCycle  = ONE_SEC;

					 if(isTimerExpire(dutyCycle, previousTime))
					 {
							turnOffLED(LED4, PORT_G);
							previousTime = getCurrentTime();
							state = LED_OFF;
							//currentTime = 0;
					 }
		   	   	   	 break;
		default: state = INITIAL;
	}

	return state;
}
