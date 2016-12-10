#include <xmc_ccu4.h>
#include <xmc_gpio.h>
#include <xmc_scu.h>
#include <xmc1_scu.h>
#include <xmc_eru.h>
#include "pwm.h"
#include "adc.h"

#include "config.h"

void stall();

int rotors = 0;

float desired_value = 0;

int stalled = 0;

int main(void) {
  XMC_GPIO_SetMode(LED1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(LED2, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(MOTOR1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(MOTOR2, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(MOTOR3_BRAKE, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);

  XMC_GPIO_SetOutputLow(LED1);
  XMC_GPIO_SetOutputLow(LED2);
  XMC_GPIO_SetOutputLow(MOTOR1);
  XMC_GPIO_SetOutputLow(MOTOR2);
  XMC_GPIO_SetOutputLow(MOTOR3_BRAKE);

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

  initRpm();


  uint8_t trigger_running = 0;
  uint8_t trigger_init = 0;
  uint8_t old_trigger_hold = 0;

  while(1) {

	float foo = (float)adcGetPotBlocking() / 1024.0;
	desired_value = foo * 23000.0;

	regulateRotors(desiredValue);

	  //rotors = XMC_GPIO_GetInput(BUTTON1);
	  //if (rotors != 1) {
		  //enableMotor1();
	  //} else {
	  //	  disableMotor1();
	  //}

		  /*
	  int trigger = !XMC_GPIO_GetInput(BUTTON2);
	  int trigger_hold = !XMC_GPIO_GetInput(BUTTON3);

	  if (!trigger_running && trigger_hold) {
		  trigger_init = 1;
		  trigger_running = 0;
	  }

	  if (!trigger_hold && trigger && !trigger_running) {
		  trigger_running = 1;
		  trigger_init = 0;
	  }

	  if (old_trigger_hold && !trigger_hold) {
		  trigger_running = 0;
		  trigger_init = 0;
	  }

	  if (trigger_running || trigger_init) {
		  enableMotor2(40000);
	  } else {
		  disableMotor2();
	  }

	  old_trigger_hold = trigger_hold;
	  */
  }

}



void SysTick_Handler(void) {
	advanceRpmCounter();
}

