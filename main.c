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

#define SYSTICK_SHIFTER 16
#define SYSTICKS_PER_SECOND (1 << SYSTICK_SHIFTER)
#define SYSTICKS_PER_MINUTE (SYSTICKS_PER_SECOND * 60.0)

float motor1_rpm = 0;
float motor2_rpm = 0;

uint32_t motor1_rotation_time = 0;
uint32_t motor2_rotation_time = 0;


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

  // init interrupt
  XMC_ERU_ETL_CONFIG_t eruInit1 = {
		  .input_a = MOTOR1_TACHOMETER_ERU_INPUT,
		  .edge_detection = XMC_ERU_ETL_EDGE_DETECTION_FALLING,
		  .enable_output_trigger = true,
		  .output_trigger_channel = XMC_ERU_ETL_OUTPUT_TRIGGER_CHANNEL0,
		  .source = XMC_ERU_ETL_SOURCE_A
  };

  XMC_ERU_ETL_CONFIG_t eruInit2 = {
		  .input_a = MOTOR2_TACHOMETER_ERU_INPUT,
		  .edge_detection = XMC_ERU_ETL_EDGE_DETECTION_FALLING,
		  .enable_output_trigger = true,
		  .output_trigger_channel = XMC_ERU_ETL_OUTPUT_TRIGGER_CHANNEL1,
		  .source = XMC_ERU_ETL_SOURCE_B
  };


  XMC_ERU_OGU_CONFIG_t oguInit = {
		  .service_request = true
  };

  XMC_ERU_ETL_Init(MOTOR1_TACHOMETER_ERU_ETL, &eruInit1);
  XMC_ERU_OGU_Init(MOTOR1_TACHOMETER_ERU_OGU, &oguInit);

  XMC_ERU_ETL_Init(MOTOR2_TACHOMETER_ERU_ETL, &eruInit2);
  XMC_ERU_OGU_Init(MOTOR2_TACHOMETER_ERU_OGU, &oguInit);

  NVIC_SetPriority(MOTOR1_TACHOMETER_ERU_IRQ, 15);
  NVIC_EnableIRQ(MOTOR1_TACHOMETER_ERU_IRQ);

  NVIC_SetPriority(MOTOR2_TACHOMETER_ERU_IRQ, 13);
  NVIC_EnableIRQ(MOTOR2_TACHOMETER_ERU_IRQ);


  uint8_t trigger_running = 0;
  uint8_t trigger_init = 0;
  uint8_t old_trigger_hold = 0;

  while(1) {

	float foo = (float)adcGetPotBlocking() / 1024.0;
	desired_value = foo * 23000.0;



   	if (desired_value < 500) {
	  stalled = 0;
	  disableMotor1();
	  disableMotor2();
    } else if (((motor1_rotation_time >= SYSTICKS_PER_SECOND) ||
    	  (motor2_rotation_time >= SYSTICKS_PER_SECOND)) &&
		(desired_value > 1500)) {
      stall();
	}

  	if (!stalled) {
		float output1 = 0.0001 * (desired_value - motor1_rpm);
		enableMotor1(output1);
		float output2 = 0.0001 * (desired_value - motor2_rpm);
		enableMotor2(output2);
  	}


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

void ERU0_0_IRQHandler(void) {
	motor1_rpm = SYSTICKS_PER_MINUTE / (float)motor1_rotation_time;
	motor1_rotation_time = 0;
	XMC_GPIO_ToggleOutput(LED1);
}

void ERU0_1_IRQHandler(void) {
	motor2_rpm = SYSTICKS_PER_MINUTE / (float)motor2_rotation_time;
	motor2_rotation_time = 0;
	XMC_GPIO_ToggleOutput(LED2);
}

void stall() {
	motor1_rotation_time = 0;
	motor1_rpm = 0;
	motor2_rotation_time = 0;
	motor2_rpm = 0;
	stalled = 1;
	disableMotor1();
	disableMotor2();
}

void SysTick_Handler(void) {
	motor1_rotation_time ++;
	motor2_rotation_time ++;
}

