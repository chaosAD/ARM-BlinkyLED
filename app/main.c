#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "LED.h"
#include "Time.h"
#include "Button.h"

int main(void)
{
	CLK_EN();
	configure(USER_INPUT, PORT_A);
	configure(LED3, PORT_G);
	configure(LED4, PORT_G);
	configure(LED5, PORT_B);
	configure(LED6, PORT_C);
	State state1 = INITIAL;
	State state2 = INITIAL;
	State state3 = INITIAL;

    while(1)
    {
    	state1 = blinkLED1(state1);
    	state2 = blinkLED2(state2);
    	state3 = blinkLED3(state3);
    	//turnOnLED3();
    	//turnOnLED4();
    	/*turnOnLED1();
    	delay(1000);
    	turnOffLED1();
      	delay(1000); */
    }
}
