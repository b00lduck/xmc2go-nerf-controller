#include "xmc_gpio.h"

#define LED1 P1_0

void SysTick_Handler(void) {
  XMC_GPIO_ToggleOutput(LED1);
}

int main(void) {
  XMC_GPIO_SetMode(LED1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);

  XMC_GPIO_ToggleOutput(LED1);

  /* System timer configuration */
  SysTick_Config(SystemCoreClock >> 1);

  while(1) {
    /* Infinite loop */
  }
}

int _init(void) {
}
