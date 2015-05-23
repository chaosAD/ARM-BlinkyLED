#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"

#define ONE_SEC					1000
#define ONE_HUND_TWENTY_MILISEC	120
#define FIFTY_MILISEC			50

#define turnOnLED1()		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET);
#define turnOffLED1()		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);
#define turnOnLED2()		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET);
#define turnOffLED2()		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);
#define turnOnLED3()		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
#define turnOffLED3()		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
#define turnOnLED4()		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);
#define turnOffLED4()		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);

typedef enum {INITIAL, LED_ON, LED_OFF} State;

void initUserButton()
{
	//GPIO_TypeDef 	 GpioType;
	GPIO_InitTypeDef GpioInfo;

	__HAL_RCC_GPIOA_CLK_ENABLE();

	GpioInfo.Mode = GPIO_MODE_INPUT;
	GpioInfo.Pin = GPIO_PIN_0;
	GpioInfo.Pull = GPIO_NOPULL;
	GpioInfo.Speed = GPIO_SPEED_HIGH;
	//GpioInfo.Alternate = GPIO_MODE_AF_PP;

	//Init LED on PA0
	HAL_GPIO_Init(GPIOA, &GpioInfo);
}

void initLED1()
{
	//GPIO_TypeDef 	 GpioType;
	GPIO_InitTypeDef GpioInfo;

	__HAL_RCC_GPIOG_CLK_ENABLE();

	GpioInfo.Mode = GPIO_MODE_OUTPUT_PP;
	GpioInfo.Pin = GPIO_PIN_13;
	GpioInfo.Pull = GPIO_NOPULL;
	GpioInfo.Speed = GPIO_SPEED_HIGH;
	//GpioInfo.Alternate = GPIO_MODE_AF_PP;

	//Init LED on PG13
	HAL_GPIO_Init(GPIOG, &GpioInfo);
}

void initLED2()
{
	//GPIO_TypeDef 	 GpioType;
	GPIO_InitTypeDef GpioInfo;

	__HAL_RCC_GPIOG_CLK_ENABLE();

	GpioInfo.Mode = GPIO_MODE_OUTPUT_PP;
	GpioInfo.Pin = GPIO_PIN_14;
	GpioInfo.Pull = GPIO_NOPULL;
	GpioInfo.Speed = GPIO_SPEED_HIGH;
	//GpioInfo.Alternate = GPIO_MODE_AF_PP;

	//Init LED on PG14
	HAL_GPIO_Init(GPIOG, &GpioInfo);
}

void initLED3()
{
	//GPIO_TypeDef 	 GpioType;
	GPIO_InitTypeDef GpioInfo;

	__HAL_RCC_GPIOB_CLK_ENABLE();

	GpioInfo.Mode = GPIO_MODE_OUTPUT_PP;
	GpioInfo.Pin = GPIO_PIN_13;
	GpioInfo.Pull = GPIO_NOPULL;
	GpioInfo.Speed = GPIO_SPEED_HIGH;
	//GpioInfo.Alternate = GPIO_MODE_AF_PP;

	//Init LED on PB13
	HAL_GPIO_Init(GPIOB, &GpioInfo);
}

void initLED4()
{
	//GPIO_TypeDef 	 GpioType;
	GPIO_InitTypeDef GpioInfo;

	//__HAL_RCC_GPIOC_CLK_ENABLE();
	__GPIOC_CLK_ENABLE();

	GpioInfo.Mode = GPIO_MODE_OUTPUT_PP;
	GpioInfo.Pin = 5;
	GpioInfo.Pull = GPIO_NOPULL;
	GpioInfo.Speed = GPIO_SPEED_FAST;
	//GpioInfo.Alternate = GPIO_MODE_AF_PP;

	//Init LED on PC5
	HAL_GPIO_Init(GPIOC, &GpioInfo);
}

uint32_t getCurrentTime()
{
	static uint32_t counter = 0;
	static uint32_t currentTime = 0;

	if(counter++ >= 100)
	{
		counter = 0;
		currentTime++;
	}

	return currentTime;
}

void delay(uint32_t delayCycle)
{
	static uint32_t previousTime = 0;

	while((getCurrentTime() - previousTime) < delayCycle);
	previousTime = getCurrentTime();
}

uint32_t isTimerExpire(uint32_t delayCycle, uint32_t previousTime)
{
	if((getCurrentTime() - previousTime) < delayCycle)
		return 0;
	else
		return 1;
}

uint32_t readUserButton()
{
	return HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
}

State blinkLED1(State state)
{
	static uint32_t previousTime = 0;
	switch(state)
	{
		case INITIAL: turnOffLED1();
					  state = LED_OFF;
					  break;
		case LED_OFF: if(isTimerExpire(ONE_HUND_TWENTY_MILISEC, previousTime))
					  {
							turnOnLED1();
							previousTime = getCurrentTime();
							state = LED_ON;
					  }
					  break;
		case LED_ON: if(isTimerExpire(ONE_HUND_TWENTY_MILISEC, previousTime))
					 {
							turnOffLED1();
							previousTime = getCurrentTime();
							state = LED_OFF;
					 }
		   	   	   	 break;
		default: state = INITIAL;
	}

	return state;
}

State blinkLED2(State state)
{
	static uint32_t previousTime = 0;
	static dutyCycle = ONE_SEC;
	switch(state)
	{
		case INITIAL: turnOffLED2();
					  state = LED_OFF;
					  break;
		case LED_OFF: if(readUserButton())
							dutyCycle = FIFTY_MILISEC;
					  else
						  	dutyCycle  = ONE_SEC;

					  if(isTimerExpire(dutyCycle, previousTime))
					  {
							turnOnLED2();
							previousTime = getCurrentTime();
							state = LED_ON;
							//currentTime = 0;
					  }
					  break;
		case LED_ON: if(readUserButton())
						dutyCycle = FIFTY_MILISEC;
					 else
						 dutyCycle  = ONE_SEC;

					 if(isTimerExpire(dutyCycle, previousTime))
					 {
							turnOffLED2();
							previousTime = getCurrentTime();
							state = LED_OFF;
							//currentTime = 0;
					 }
		   	   	   	 break;
		default: state = INITIAL;
	}

	return state;
}

State blinkLED3(State state)
{
	static uint32_t previousTime = 0;
	static uint32_t blinkTime = 0;
	switch(state)
	{
		case INITIAL: turnOffLED3();
					  if(readUserButton())
						  state = LED_OFF;
					  else
						  state = INITIAL;
					  break;
		case LED_OFF: if(isTimerExpire(ONE_SEC, previousTime))
					  {
							turnOnLED3();
							previousTime = getCurrentTime();
							state = LED_ON;
					  }
					  break;
		case LED_ON: if(blinkTime == 5)
					 {
						state = INITIAL;
						blinkTime = 0;
					 }
					 else
					 {
						 if(isTimerExpire(ONE_SEC, previousTime))
						 {
							 turnOffLED3();
							 previousTime = getCurrentTime();
							 state = LED_OFF;
							 blinkTime++;
						 }
					 }
		   	   	   	 break;
		default: state = INITIAL;
	}

	return state;
}

int main(void)
{
	initUserButton();
	initLED1();
	initLED2();
	initLED3();
	initLED4();
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
