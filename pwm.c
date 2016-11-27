#include <xmc_ccu4.h>
#include <xmc_gpio.h>
#include <xmc_scu.h>
#include <xmc1_scu.h>

#include "pwm.h"
#include "config.h"

/* Prepare configuration */
XMC_CCU4_SLICE_COMPARE_CONFIG_t SLICE0_config = {
	  .timer_mode = (uint32_t) XMC_CCU4_SLICE_TIMER_COUNT_MODE_EA,
	  .monoshot = (uint32_t) false,
	  .shadow_xfer_clear = (uint32_t) 0,
	  .dither_timer_period = (uint32_t) 0,
	  .dither_duty_cycle = (uint32_t) 0,
	  .prescaler_mode = (uint32_t) XMC_CCU4_SLICE_PRESCALER_MODE_NORMAL,
	  .mcm_enable = (uint32_t) 0,
	  .prescaler_initval = (uint32_t) 1, /* in this case, prescaler = 2^10 */
	  .float_limit = (uint32_t) 0,
	  .dither_limit = (uint32_t) 0,
	  .passive_level = (uint32_t) XMC_CCU4_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
	  .timer_concatenation = (uint32_t) 0
};

XMC_GPIO_CONFIG_t SLICE0_OUTPUT_config = {
	  .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT4,
	  .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
	  .output_level = XMC_GPIO_OUTPUT_LEVEL_LOW,
};

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

	  /* Initialize the Slice */
	  XMC_CCU4_SLICE_CompareInit(SLICE0_PTR, &SLICE0_config);

	  /* Program duty cycle = 33.33% at 1Hz frequency */
	  XMC_CCU4_SLICE_SetTimerCompareMatch(SLICE0_PTR, 65499U);
	  XMC_CCU4_SLICE_SetTimerPeriodMatch(SLICE0_PTR, 65499U);

	  /* Enable shadow transfer */
	  XMC_CCU4_EnableShadowTransfer(MODULE_PTR, (uint32_t)(XMC_CCU4_SHADOW_TRANSFER_SLICE_0|XMC_CCU4_SHADOW_TRANSFER_PRESCALER_SLICE_0));

	  /* Enable External Start to Event 0 */
	  /* Initialize the Slice */
	  XMC_CCU4_SLICE_CompareInit(SLICE0_PTR, &SLICE0_config);

	  /* Program duty cycle = 33.33% at 1Hz frequency */
	  XMC_CCU4_SLICE_SetTimerCompareMatch(SLICE0_PTR, 65499U);
	  XMC_CCU4_SLICE_SetTimerPeriodMatch(SLICE0_PTR, 65499U);

	  /* Enable shadow transfer */
	  XMC_CCU4_EnableShadowTransfer(MODULE_PTR, (uint32_t)(XMC_CCU4_SHADOW_TRANSFER_SLICE_0|XMC_CCU4_SHADOW_TRANSFER_PRESCALER_SLICE_0));

	  enableMotor1();

	  /* Get the slice out of idle mode */
	  XMC_CCU4_EnableClock(MODULE_PTR, SLICE0_NUMBER);

	  XMC_CCU4_SLICE_StartTimer(SLICE0_PTR);

	  /* Enable CCU4 PWM output */
	  XMC_GPIO_Init(SLICE0_OUTPUT, &SLICE0_OUTPUT_config);

	  /* Get the slice out of idle mode */
	  XMC_CCU4_EnableClock(MODULE_PTR, SLICE0_NUMBER);

	  XMC_CCU4_SLICE_StartTimer(SLICE0_PTR);
}

void enableMotor1() {
	/* Enable CCU4 PWM output */
	  XMC_GPIO_Init(SLICE0_OUTPUT, &SLICE0_OUTPUT_config);
}

void disableMotor1() {
	  XMC_GPIO_SetMode(MOTOR1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
	  XMC_GPIO_SetOutputLow(MOTOR1);
}

void initMotor2() {

}

void enableMotor2() {
}

void disableMotor2() {
}
