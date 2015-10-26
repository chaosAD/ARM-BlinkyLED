#ifndef __Rcc_H__
#define __Rcc_H__

#include <stdint.h>
#include "Gpio.h"

#define RCC_BASE_ADDRESS	0x40023800
#define rcc   				((RccType *)RCC_BASE_ADDRESS)

typedef struct RCC_t RccType;
struct RCC_t {
  volatile uint32_t RCC_CR;
  volatile uint32_t RCC_PLLCFGR;
  volatile uint32_t RCC_CFGR;
  volatile uint32_t RCC_CIR;
  volatile uint32_t RCC_AHB1RSTR;
  volatile uint32_t RCC_AHB2RSTR;
  volatile uint32_t RCC_AHB3RSTR;
  volatile uint32_t Reserved1;
  volatile uint32_t RCC_APB1RSTR;
  volatile uint32_t RCC_APB2RSTR;
  volatile uint32_t Reserved2[2];
  volatile uint32_t RCC_AHB1ENR;
  volatile uint32_t RCC_AHB2ENR;
  volatile uint32_t RCC_AHB3ENR;
  volatile uint32_t Reserved3;
  volatile uint32_t RCC_APB1ENR;
  volatile uint32_t RCC_APB2ENR;
  volatile uint32_t Reserved4[2];
  volatile uint32_t RCC_AHB1LPENR;
  volatile uint32_t RCC_AHB2LPENR;
  volatile uint32_t RCC_AHB3LPENR;
  volatile uint32_t Reserved5;
  volatile uint32_t RCC_APB1LPENR;
  volatile uint32_t RCC_APB2LPENR;
  volatile uint32_t Reserved6[2];
  volatile uint32_t RCC_BDCR;
  volatile uint32_t RCC_CSR;
  volatile uint32_t Reserved7[2];
  volatile uint32_t RCC_SSCGR;
  volatile uint32_t RCC_PLLI2SCFGR;
};

void gpioUnresetEnableClock(GpioType *port);

#endif	// __Rcc_H__
