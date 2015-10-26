#include "Rcc.h"
#include "Gpio.h"
//#include "stm32f4xx_hal_rcc.h"

void gpioUnresetEnableClock(GpioType *port) {
  rcc->RCC_APB1RSTR &= ~(1 << getGpioIndex(port));
  rcc->RCC_AHB1ENR |= 1 << getGpioIndex(port);
}
