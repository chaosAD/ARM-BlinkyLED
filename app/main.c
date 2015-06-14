#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "Time.h"
#include "LED.h"
#include "Button.h"
#include "State.h"

int main(void)
{
	initUserButton();
	CLK_EN();
	configureLED(LED3, PORTG);
	configureLED(LED4, PORTG);
	configureLED(LED5, PORTB);
	configureLED(LED6, PORTC);
	State state1 = INITIAL;
	State state2 = INITIAL;
	State state3 = INITIAL;

    while(1)
    {
    	updateTime();
    	state1 = blinkLED1(state1);
    	state2 = blinkLED2(state2);
    	state3 = blinkLED3(state3);

    	//turnOnLED(PORTG, LED3);
    	//turnOnLED(PORTG, LED4);
    	//turnOnLED(PORTB, LED5);
    	//turnOnLED(PORTC, LED6);
    	//delay(1000);
    	//turnOffLED1();
      	//delay(1000);
    }
}
