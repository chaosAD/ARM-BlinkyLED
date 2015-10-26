#include "Gpio.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_rcc.h"

#define enableGpioG		(ptr[0x30/4] |= 1 << 6,	\
						ptr[0x10/4] &= ~(1 << 6))

void configurePin(int mode, int pinNum, GpioType *port) {
//	GPIO_InitTypeDef GpioInfo;

//	__HAL_RCC_GPIOG_CLK_ENABLE();
//	__HAL_RCC_GPIOC_CLK_ENABLE();
//	__HAL_RCC_GPIOB_CLK_ENABLE();
//	uint32_t *ptr = (uint32_t *)0x40023800;
//	enableGpioG;

	gpioUnresetEnableClock(port);
//	gpioUnresetEnableClock(PORTC);
//	gpioUnresetEnableClock(PORTB);

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
	port->OSPEED |= PORT_HIGH_SPEED << (pinNum * 2);

/*
	GpioInfo.Mode = direction;
	GpioInfo.Pin = pinNum;
	GpioInfo.Pull = GPIO_NOPULL;
	GpioInfo.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(port, &GpioInfo);
*/
}

void writeOne(int pinNum, GpioType *port) {
//  HAL_GPIO_WritePin(port, pinNum, GPIO_PIN_SET);
  port->ODR |= 1 << pinNum;
}

void writeZero(int pinNum, GpioType *port) {
//  HAL_GPIO_WritePin(port, pinNum, GPIO_PIN_RESET);
  port->ODR &= ~(1 << pinNum);
}
