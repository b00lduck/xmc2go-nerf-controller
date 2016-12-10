#include <xmc_ccu4.h>
#include <xmc_gpio.h>
#include <xmc_scu.h>
#include <xmc1_scu.h>

#include "pwm.h"
#include "config.h"

/* Prepare configuration */
XMC_CCU4_SLICE_COMPARE_CONFIG_t SLICE_config = {
	  .timer_mode = (uint32_t) XMC_CCU4_SLICE_TIMER_COUNT_MODE_EA,
	  .monoshot = (uint32_t) false,
	  .shadow_xfer_clear = (uint32_t) 0,
	  .dither_timer_period = (uint32_t) 0,
	  .dither_duty_cycle = (uint32_t) 0,
	  .prescaler_mode = (uint32_t) XMC_CCU4_SLICE_PRESCALER_MODE_NORMAL,
	  .mcm_enable = (uint32_t) 0,
	  .prescaler_initval = (uint32_t) 1,
	  .float_limit = (uint32_t) 0,
	  .dither_limit = (uint32_t) 0,
	  .passive_level = (uint32_t) XMC_CCU4_SLICE_OUTPUT_PASSIVE_LEVEL_HIGH,
	  .timer_concatenation = (uint32_t) 0
};

XMC_GPIO_CONFIG_t SLICE_OUTPUT_config = {
	  .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT4,
	  .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
	  .output_level = XMC_GPIO_OUTPUT_LEVEL_LOW,
};

int speedFloatToInt(float speed) {
	if (speed > 1.0) speed = 1.0;
	if (speed < 0.0) speed = 0.0;
	return TIMER_PERIOD * speed;
}

void initPwm() {

	  /* Enable clock, enable prescaler block and configure global control */
	  XMC_CCU4_Init(MODULE_PTR, XMC_CCU4_SLICE_MCMS_ACTION_TRANSFER_PR_CR);

	  /* Start the prescaler and restore clocks to slices */
	  XMC_CCU4_StartPrescaler(MODULE_PTR);

	  /* Start of CCU4 configurations */
	  /* Ensure fCCU reaches CCU40 */
	  XMC_CCU4_SetModuleClock(MODULE_PTR, XMC_CCU4_CLOCK_SCU);

	  initMotor1();
	  initMotor2();

}

void initMotor1() {
	  XMC_CCU4_SLICE_CompareInit(SLICE0_PTR, &SLICE_config);
	  XMC_CCU4_SLICE_SetTimerPeriodMatch(SLICE0_PTR, TIMER_PERIOD);
	  XMC_CCU4_EnableShadowTransfer(MODULE_PTR, (uint32_t)(XMC_CCU4_SHADOW_TRANSFER_SLICE_0));
	  enableMotor1(TIMER_PERIOD-1);
	  XMC_CCU4_EnableClock(MODULE_PTR, SLICE0_NUMBER);
	  XMC_CCU4_SLICE_StartTimer(SLICE0_PTR);
}

int motor1enabled = 0;
void enableMotor1(float speed) {
	XMC_CCU4_SLICE_SetTimerCompareMatch(SLICE0_PTR, speedFloatToInt(speed));
	XMC_CCU4_EnableShadowTransfer(MODULE_PTR, (uint32_t)(XMC_CCU4_SHADOW_TRANSFER_SLICE_0));
	if (!motor1enabled) {
		motor1enabled = 1;
		XMC_GPIO_Init(SLICE0_OUTPUT, &SLICE_OUTPUT_config);
	}
}

void disableMotor1() {
	  motor1enabled = 0;
	  XMC_GPIO_SetMode(SLICE0_OUTPUT, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
	  XMC_GPIO_SetOutputLow(SLICE0_OUTPUT);
}

void initMotor2() {
	  XMC_CCU4_SLICE_CompareInit(SLICE1_PTR, &SLICE_config);
	  XMC_CCU4_SLICE_SetTimerPeriodMatch(SLICE1_PTR, TIMER_PERIOD);
	  XMC_CCU4_EnableShadowTransfer(MODULE_PTR, (uint32_t)(XMC_CCU4_SHADOW_TRANSFER_SLICE_1));
	  enableMotor2(TIMER_PERIOD-1);
	  XMC_CCU4_EnableClock(MODULE_PTR, SLICE1_NUMBER);
	  XMC_CCU4_SLICE_StartTimer(SLICE1_PTR);
}

int motor2enabled = 0;
void enableMotor2(float speed) {
	XMC_CCU4_SLICE_SetTimerCompareMatch(SLICE1_PTR, speedFloatToInt(speed));
	XMC_CCU4_EnableShadowTransfer(MODULE_PTR, (uint32_t)(XMC_CCU4_SHADOW_TRANSFER_SLICE_1));
	if (!motor2enabled) {
		motor2enabled = 1;
		XMC_GPIO_Init(SLICE1_OUTPUT, &SLICE_OUTPUT_config);
	}
}

void disableMotor2() {
	motor2enabled = 0;
	XMC_GPIO_SetMode(SLICE1_OUTPUT, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
	XMC_GPIO_SetOutputLow(SLICE1_OUTPUT);
}

/*
void enableMotor3(int speed) {
	XMC_CCU4_SLICE_SetTimerCompareMatch(SLICE1_PTR, speed);
	XMC_CCU4_EnableShadowTransfer(MODULE_PTR, (uint32_t)(XMC_CCU4_SHADOW_TRANSFER_SLICE_1));
	if (!motor2enabled) {
		motor2enabled = 1;
		XMC_GPIO_SetOutputLow(MOTOR3_BRAKE);
		XMC_GPIO_Init(SLICE1_OUTPUT, &SLICE_OUTPUT_config);
	}
}

void disableMotor3() {
	motor2enabled = 0;
	XMC_GPIO_SetMode(SLICE1_OUTPUT, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
	XMC_GPIO_SetOutputLow(SLICE1_OUTPUT);
	XMC_GPIO_SetOutputHigh(MOTOR3_BRAKE);
}
*/
