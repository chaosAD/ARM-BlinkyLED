#include "Gpio.h"
#include "stm32f4xx_hal_rcc.h"



void configurePin(int mode, int pinNum, GPIO *port) {
	GPIO_InitTypeDef GpioInfo;

	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
/*
	int *ptr = (int *)0x40021800;
	ptr[0] = 0x10000000;				// MODE.pin14 = ouput
	ptr[1] = 0; 						// OTYPE.pin14 = push-pull
	ptr[2] = 0x20000000;				// OSPEED.pin14 = high speed
*/
	// ((GPIO *)GPIOG_BASE_ADDRESS)
	port->MODER &= ~(3 << (pinNum * 2));
	port->MODER |= (mode << (pinNum * 2));
	port->OTYPER &= ~(1 << pinNum);	// Set to pin to push-pull
	port->OSPEED &= ~(3 << (pinNum * 2));
	port->OSPEED |= GPIO_HIGH_SPEED << (pinNum * 2);

/*
	GpioInfo.Mode = direction;
	GpioInfo.Pin = pinNum;
	GpioInfo.Pull = GPIO_NOPULL;
	GpioInfo.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(port, &GpioInfo);
*/
}

void writeOne(int pinNum, GPIO_TypeDef *port) {
  HAL_GPIO_WritePin(port, pinNum, GPIO_PIN_SET);
}

void writeZero(int pinNum, GPIO_TypeDef *port) {
  HAL_GPIO_WritePin(port, pinNum, GPIO_PIN_RESET);
}
