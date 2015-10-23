#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "Time.h"
#include "LED.h"
#include "Button.h"
#include "State.h"

#include "Gpio.h"

void delay_(uint32_t delayCount) {
  while(delayCount--);
}

int main(void)
{

	configurePin(GPIO_MODE_OUTPUT, PIN_14, PORTG);
	configurePin(GPIO_MODE_OUTPUT, PIN_13, PORTB);
	while(1) {
	  writeOne(GPIO_PIN_14, GPIOG);
	  writeOne(GPIO_PIN_13, GPIOB);
	  delay_(200000);
	  writeZero(GPIO_PIN_14, GPIOG);
	  writeZero(GPIO_PIN_13, GPIOB);
	  delay_(200000);
	}







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
    	turnOnLED(PORTG, LED3);
    	turnOffLED(PORTG, LED3);

/*
    	updateTime();
    	state1 = blinkLED1(state1);
    	state2 = blinkLED2(state2);
    	state3 = blinkLED3(state3);
*/
    	//turnOnLED(PORTG, LED3);
    	//turnOnLED(PORTG, LED4);
    	//turnOnLED(PORTB, LED5);
    	//turnOnLED(PORTC, LED6);
    	//delay(1000);
    	//turnOffLED1();
      	//delay(1000);
    }
}
