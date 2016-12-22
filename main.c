#include <xmc_ccu4.h>
#include <xmc_gpio.h>
#include <xmc_scu.h>
#include <xmc1_scu.h>
#include "pwm.h"
#include "adc.h"
#include "rpm.h"
#include "config.h"

int rotors = 0;

int main(void) {

  // Configure GPIOs
  XMC_GPIO_SetMode(LED1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(LED2, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(MOTOR1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(MOTOR2, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(MOTOR3, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(MOTOR3_BRAKE, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);

  XMC_GPIO_SetOutputLow(LED1);
  XMC_GPIO_SetOutputLow(LED2);
  XMC_GPIO_SetOutputLow(MOTOR1);
  XMC_GPIO_SetOutputLow(MOTOR2);
  XMC_GPIO_SetOutputLow(MOTOR3);
  XMC_GPIO_SetOutputHigh(MOTOR3_BRAKE);

  XMC_GPIO_SetMode(BUTTON1, XMC_GPIO_MODE_INPUT_PULL_UP);
  XMC_GPIO_SetMode(BUTTON2, XMC_GPIO_MODE_INPUT_PULL_UP);
  XMC_GPIO_SetMode(BUTTON3, XMC_GPIO_MODE_INPUT_PULL_UP);
  XMC_GPIO_SetMode(MOTOR1_TACHOMETER, XMC_GPIO_MODE_INPUT_PULL_UP);
  XMC_GPIO_SetMode(MOTOR2_TACHOMETER, XMC_GPIO_MODE_INPUT_PULL_UP);

  XMC_GPIO_EnableDigitalInput(BUTTON1);
  XMC_GPIO_EnableDigitalInput(BUTTON2);
  XMC_GPIO_EnableDigitalInput(BUTTON3);
  XMC_GPIO_EnableDigitalInput(MOTOR1_TACHOMETER);
  XMC_GPIO_EnableDigitalInput(MOTOR2_TACHOMETER);

  // Configure SysTick
  SysTick_Config(SystemCoreClock / SYSTICKS_PER_SECOND);
  XMC_SCU_CLOCK_CONFIG_t clock_config = {
		  .pclk_src = XMC_SCU_CLOCK_PCLKSRC_DOUBLE_MCLK,
		  .rtc_src = XMC_SCU_CLOCK_RTCCLKSRC_DCO2,
		  .fdiv = 0,
		  .idiv = 1,
  };
  XMC_SCU_CLOCK_Init(&clock_config);

  initPwm();
  initAdc();

  uint8_t pusher_state = 0;

  while(1) {

	// ROTORS CONTROL
	float foo = (float)adcGetPotBlocking() / 512.0;

	rotors = XMC_GPIO_GetInput(BUTTON3);
	if (rotors != 1) {
		regulateRotors(MAX_RPM * foo);
	} else {
		regulateRotors(0);
	}

	// PUSHER CONTROL
	uint8_t trigger = !XMC_GPIO_GetInput(BUTTON2);
	uint8_t trigger_hold = !XMC_GPIO_GetInput(BUTTON1);

	switch (pusher_state) {

	  	// State 0: resting in "zero" position
		case 0:
			XMC_GPIO_SetOutputLow(LED1);
			XMC_GPIO_SetOutputLow(LED2);
			disableMotor3();
			if (trigger) {
				pusher_state = 1;
			}
			break;

		// State 1: shot requested
		case 1:
			XMC_GPIO_SetOutputLow(LED2);
			XMC_GPIO_SetOutputHigh(LED1);
			enableMotor3(1);
			if (trigger_hold) {
				pusher_state = 2;
			}
			break;

		// State 2: shot in progress
		case 2:
			XMC_GPIO_SetOutputLow(LED1);
			XMC_GPIO_SetOutputHigh(LED2);
			enableMotor3(0.5);
			if (!trigger_hold) {
				pusher_state = 3;
			}
			break;

		// State 3: shot done, waiting for trigger cycle
		case 3:
			XMC_GPIO_SetOutputHigh(LED1);
			XMC_GPIO_SetOutputHigh(LED2);
			disableMotor3();
			if (!trigger) {
				pusher_state = 0;
			}
			break;

	}

  }

}

void SysTick_Handler(void) {
	advanceRpmCounter();
}

