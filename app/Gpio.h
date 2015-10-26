#ifndef __Gpio_H__
#define __Gpio_H__

#include <stdint.h>
#include "stm32f4xx_hal_gpio.h"

#define getGpioIndex(x)	(((uint32_t)(x) - (uint32_t)GPIOA_BASE_ADDRESS) / 0x400)
#define GPIO_OUTPUT		GPIO_MODE_OUTPUT_PP
#define GPIO_INPUT		GPIO_MODE_INPUT

typedef struct GPIO_t GpioType;
struct GPIO_t {
	uint32_t MODER;
	uint32_t OTYPER;
	uint32_t OSPEED;
	uint32_t PUPDR;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
	uint32_t LCKR;
	uint32_t AFRL;
	uint32_t AFRH;
};

#define PIN_0			0
#define PIN_1			1
#define PIN_2			2
#define PIN_3			3
#define PIN_4			4
#define PIN_5			5
#define PIN_6			6
#define PIN_7			7
#define PIN_8			8
#define PIN_9			9
#define PIN_10			10
#define PIN_11			11
#define PIN_12			12
#define PIN_13			13
#define PIN_14			14
#define PIN_15			15

#define PORT_MODE_INPUT		0
#define PORT_MODE_OUTPUT	1
#define PORT_MODE_ALTFUNC	2
#define PORT_MODE_ANALOG	3

#define PORT_LOW_SPEED        0
#define PORT_MEDIUM_SPEED     1
#define PORT_HIGH_SPEED       2
#define PORT_VERY_HIGH_SPEED  3

#define GPIOG_BASE_ADDRESS	0x40021800
#define GPIOC_BASE_ADDRESS	0x40020800
#define GPIOB_BASE_ADDRESS	0x40020400
#define GPIOA_BASE_ADDRESS	0x40020000

#define PORTG   ((GpioType *)GPIOG_BASE_ADDRESS)
#define PORTC   ((GpioType *)GPIOC_BASE_ADDRESS)
#define PORTB   ((GpioType *)GPIOB_BASE_ADDRESS)

void configurePin(int mode, int pinNum, GpioType *port);
void writeOne(int pinNum, GpioType *port);
void writeZero(int pinNum, GpioType *port);

#endif	// __Gpio_H__
