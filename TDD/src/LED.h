#ifndef LED_H
#define LED_H

typedef enum {INITIAL, LED_ON, LED_OFF, WAIT_FOR_RELEASE} State;

#define USER_INPUT	GPIO_PIN_0
#define LED3		GPIO_PIN_13
#define LED4		GPIO_PIN_14
#define LED5		GPIO_PIN_13
#define LED6		GPIO_PIN_5

#define PORT_A	GPIOA
#define PORT_B	GPIOB
#define PORT_C	GPIOC
#define PORT_G	GPIOG

#define turnOnLED(pin, port)		HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
#define turnOffLED(pin, port)		HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);

#define CLK_EN()	do{									\
						__HAL_RCC_GPIOA_CLK_ENABLE();	\
						__HAL_RCC_GPIOB_CLK_ENABLE();	\
						__HAL_RCC_GPIOC_CLK_ENABLE();	\
						__HAL_RCC_GPIOG_CLK_ENABLE();	\
					}while(0)

#define configure(pin, port)	do{											\
									GPIO_InitTypeDef GpioInfo;				\
																			\
									GpioInfo.Mode = GPIO_MODE_OUTPUT_PP;	\
									GpioInfo.Pin = pin;						\
									GpioInfo.Pull = GPIO_NOPULL;			\
									GpioInfo.Speed = GPIO_SPEED_HIGH;		\
																			\
									HAL_GPIO_Init(port, &GpioInfo);			\
								}while(0)

State blinkLED1(State state);
State blinkLED2(State state);
State blinkLED3(State state);

#endif // LED_H
