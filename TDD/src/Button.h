#ifndef BUTTON_H
#define BUTTON_H

#define	readUserButton()	HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)
/*
uint32_t readUserButton()
{
	return HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
}
*/
#endif // BUTTON_H
