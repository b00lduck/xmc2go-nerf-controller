#include <xmc_ccu4.h>
#include <xmc_gpio.h>
#include <xmc_scu.h>
#include <xmc1_scu.h>

#define LED1 P1_1
#define LED2 P1_0

#define MODULE_PTR CCU40
#define MODULE_NUMBER (0U)
#define SLICE0_PTR CCU40_CC40
#define SLICE0_NUMBER (0U)
#define SLICE0_OUTPUT LED2

#define CALCULATE_PERIOD(interval_in_ms) ((15625 * interval_in_ms) / 1000) /* f=64MHz; Prescaler set to 4096 */

int _init(void) {}

void SysTick_Handler(void) {
  XMC_GPIO_ToggleOutput(LED1);
}

int main(void) {
  XMC_GPIO_SetMode(LED1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(LED2, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);

  XMC_GPIO_SetOutputLow(LED1);
  XMC_GPIO_SetOutputLow(LED2);

  /* System timer configuration */
  SysTick_Config(SystemCoreClock >> 4);




  XMC_SCU_CLOCK_CONFIG_t clock_config = {
		  .pclk_src = XMC_SCU_CLOCK_PCLKSRC_DOUBLE_MCLK,
		  .rtc_src = XMC_SCU_CLOCK_RTCCLKSRC_DCO2,
		  .fdiv = 0,
		  .idiv = 1,
  };

  /* Prepare configuration */
  XMC_CCU4_SLICE_COMPARE_CONFIG_t SLICE0_config = {
		  .timer_mode = (uint32_t) XMC_CCU4_SLICE_TIMER_COUNT_MODE_EA,
		  .monoshot = (uint32_t) false,
		  .shadow_xfer_clear = (uint32_t) 0,
		  .dither_timer_period = (uint32_t) 0,
		  .dither_duty_cycle = (uint32_t) 0,
		  .prescaler_mode = (uint32_t) XMC_CCU4_SLICE_PRESCALER_MODE_NORMAL,
		  .mcm_enable = (uint32_t) 0,
		  .prescaler_initval = (uint32_t) 4, /* in this case, prescaler = 2^10 */
		  .float_limit = (uint32_t) 0,
		  .dither_limit = (uint32_t) 0,
		  .passive_level = (uint32_t) XMC_CCU4_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
		  .timer_concatenation = (uint32_t) 0
  };

  XMC_GPIO_CONFIG_t SLICE0_OUTPUT_config = {
		  .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
		  .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
		  .output_level = XMC_GPIO_OUTPUT_LEVEL_LOW,
  };

  XMC_CCU4_SLICE_EVENT_CONFIG_t SLICE0_event0_config = {
		  .mapped_input = XMC_CCU4_SLICE_INPUT_I, /* mapped to SCU.GSC40 */
		  .edge = XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_RISING_EDGE,
		  .level = XMC_CCU4_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_HIGH,
		  .duration = XMC_CCU4_SLICE_EVENT_FILTER_3_CYCLES
  };


  /* Ensure clock frequency is set at 64MHz (2*MCLK) */
  XMC_SCU_CLOCK_Init(&clock_config);

  /* Enable clock, enable prescaler block and configure global control */
  XMC_CCU4_Init(MODULE_PTR, XMC_CCU4_SLICE_MCMS_ACTION_TRANSFER_PR_CR);

  /* Start the prescaler and restore clocks to slices */
  XMC_CCU4_StartPrescaler(MODULE_PTR);

  /* Start of CCU4 configurations */
  /* Ensure fCCU reaches CCU40 */
  XMC_CCU4_SetModuleClock(MODULE_PTR, XMC_CCU4_CLOCK_SCU);

  /* Initialize the Slice */
  XMC_CCU4_SLICE_CompareInit(SLICE0_PTR, &SLICE0_config);

  /* Program duty cycle = 33.33% at 1Hz frequency */
  XMC_CCU4_SLICE_SetTimerCompareMatch(SLICE0_PTR, 60000U);
  XMC_CCU4_SLICE_SetTimerPeriodMatch(SLICE0_PTR, 62499U);

  /* Enable shadow transfer */
  XMC_CCU4_EnableShadowTransfer(MODULE_PTR, (uint32_t)(XMC_CCU4_SHADOW_TRANSFER_SLICE_0|XMC_CCU4_SHADOW_TRANSFER_PRESCALER_SLICE_0));

  /* Enable External Start to Event 0 */
  XMC_CCU4_SLICE_ConfigureEvent(SLICE0_PTR, XMC_CCU4_SLICE_EVENT_0, &SLICE0_event0_config);
  XMC_CCU4_SLICE_StartConfig(SLICE0_PTR, XMC_CCU4_SLICE_EVENT_0, XMC_CCU4_SLICE_START_MODE_TIMER_START_CLEAR);

  /* Enable CCU4 PWM output */
  XMC_GPIO_Init(SLICE0_OUTPUT, &SLICE0_OUTPUT_config);

  /* Get the slice out of idle mode */
  XMC_CCU4_EnableClock(MODULE_PTR, SLICE0_NUMBER);

  XMC_CCU4_SLICE_StartTimer(SLICE0_PTR);


  while(1) {
    /* Infinite loop */
  }
}

void CCU40_1_IRQHandler(void) {
  XMC_GPIO_ToggleOutput(LED2);
  return;
}
