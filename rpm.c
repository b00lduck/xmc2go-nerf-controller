#include "rpm.h"
#include "config.h"
#include "pwm.h"
#include <xmc_eru.h>
#include <xmc_gpio.h>

uint16_t motor1_rpm = 0;
uint16_t motor2_rpm = 0;

uint16_t motor1_rotation_time = 0;
uint16_t motor2_rotation_time = 0;

uint8_t stalled = 0;

void initRpm() {

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

}

void ERU0_0_IRQHandler(void) {
	motor1_rpm = (float)SYSTICKS_PER_MINUTE / (float)motor1_rotation_time;
	motor1_rotation_time = 0;
	XMC_GPIO_ToggleOutput(LED1);
}

void ERU0_1_IRQHandler(void) {
	motor2_rpm = (float)SYSTICKS_PER_MINUTE / (float)motor2_rotation_time;
	motor2_rotation_time = 0;
	XMC_GPIO_ToggleOutput(LED2);
}
