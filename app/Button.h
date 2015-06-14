#ifndef Button_H
#define Button_H

#include "stm32f4xx_hal_gpio.h"
#define	readUserButton()	HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)

void initUserButton();

#endif // Button_H
