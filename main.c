#include <xmc_ccu4.h>
#include <xmc_gpio.h>
#include <xmc_scu.h>
#include <xmc1_scu.h>
#include <xmc_vadc.h>
#include "pwm.h"
#include "adc.h"
#include "pusher.h"
#include "config.h"
#include "rotors.h"

uint8_t general_error = 0;

int main(void) {

  // Configure GPIOs
  XMC_GPIO_SetMode(LED1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(LED2, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(LED3, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(LED4, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);

  XMC_GPIO_SetMode(MOTOR1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(MOTOR2, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(MOTOR3, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(MOTOR3_BRAKE, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);

  XMC_GPIO_SetOutputLow(MOTOR1);
  XMC_GPIO_SetOutputLow(MOTOR2);
  XMC_GPIO_SetOutputLow(MOTOR3);
  XMC_GPIO_SetOutputHigh(MOTOR3_BRAKE);

  XMC_GPIO_SetMode(BUTTON2, XMC_GPIO_MODE_INPUT_PULL_UP);
  XMC_GPIO_SetMode(BUTTON3, XMC_GPIO_MODE_INPUT_PULL_UP);
  XMC_GPIO_SetMode(MOTOR1_TACHOMETER, XMC_GPIO_MODE_INPUT_PULL_UP);
  XMC_GPIO_SetMode(MOTOR2_TACHOMETER, XMC_GPIO_MODE_INPUT_PULL_UP);

  XMC_GPIO_SetMode(BUTTON3, XMC_GPIO_MODE_INPUT_TRISTATE);
  XMC_GPIO_SetMode(LIGHT_BARRIER1, XMC_GPIO_MODE_INPUT_TRISTATE);

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

  for (uint32_t i=0;i<200000;i++) {
	  XMC_GPIO_SetOutputHigh(LED1);
  }

  initPwm();
  initAdc();

  float pot_value = 0;

  int battery = 0;
  uint16_t low_battery_counter = 0;

  XMC_GPIO_SetOutputLow(LED1);
  XMC_GPIO_SetOutputHigh(LED4);

  while(1) {

	// Read ADC values
    adcProcess(&pot_value, &battery);

	// Securtiy checks/shutdown
    if (rotors_stalled) {
    	general_error = 1;
    }

    if (pusher_stalled) {
    	general_error = 1;
    }

	if (battery < BATTERY_LOW_THRESHOLD) {
		low_battery_counter++;
		if (low_battery_counter > BATTERY_LOW_COUNTER_LIMIT) {
			general_error = 1;
		}
	} else {
		low_battery_counter = 0;
	}

    if (general_error) {
    	regulateRotors(0);
		disableMotor3();
		pusher_state = 0;
		XMC_GPIO_SetOutputLow(LED4);
		XMC_GPIO_SetOutputLow(LED1);
		XMC_GPIO_SetOutputLow(LED3);
		XMC_GPIO_SetOutputHigh(LED2);
	} else {
		uint8_t ammo_ready = XMC_GPIO_GetInput(LIGHT_BARRIER1);
		processRotors(pot_value, ammo_ready);
		processPusher(ammo_ready);
	}
  }
}

void SysTick_Handler(void) {
	advanceRotorsCounter();
	advancePusherCounter();
}
