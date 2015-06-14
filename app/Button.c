#include "Button.h"

void initUserButton()
{
	//GPIO_TypeDef 	 GpioType;
	GPIO_InitTypeDef GpioInfo;

	//__HAL_RCC_GPIOA_CLK_ENABLE();

	GpioInfo.Mode = GPIO_MODE_INPUT;
	GpioInfo.Pin = GPIO_PIN_0;
	GpioInfo.Pull = GPIO_NOPULL;
	GpioInfo.Speed = GPIO_SPEED_HIGH;
	//GpioInfo.Alternate = GPIO_MODE_AF_PP;

	//Init LED on PA0
	HAL_GPIO_Init(GPIOA, &GpioInfo);
}
