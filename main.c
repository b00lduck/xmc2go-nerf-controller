#include "xmc_ccu4.h"
#include "xmc_gpio.h"

#define LED1 P1_0
#define LED2 P1_1

#define CALCULATE_PERIOD(interval_in_ms) ((35155 * interval_in_ms) / 1000) /* fCPU=144MHz; Prescaler set to 4096 */

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

//  uint32_t timer_interval = 1000;
//  bool button_edge = true;


  /* INITIALIZE CCU40 FOR TOGGLING OF LED */

  /* Initialize CCU40 */
  XMC_CCU4_Init(CCU40, XMC_CCU4_SLICE_MCMS_ACTION_TRANSFER_PR_CR);

  /* Enable the clock for selected timer */
  XMC_CCU4_EnableClock(CCU40, 3);

  /* Prepare configuration */
  XMC_CCU4_SLICE_COMPARE_CONFIG_t slice_config =  {
                                                    .tc = 0,
                                                    .prescaler_initval = 12, /* set pre-scaler to 4096 */
                                                    .float_limit = 0,
                                                    .dither_limit = 0,
                                                    .passive_level = 0,
                                                    .timer_concatenation = 0
                                                  };

  /* Configure the timer */
  XMC_CCU4_SLICE_CompareInit(CCU40_CC43, &slice_config);

  /* programs the timer period register according to time interval value */
  XMC_CCU4_SLICE_SetTimerPeriodMatch(CCU40_CC43, 35155); /*initial period is 1s. fCPU / pre-scaler = 144E6 / 4096 = 35155*/

  /* Transfers value from shadow timer registers to actual timer registers */
  XMC_CCU4_EnableShadowTransfer(CCU40, XMC_CCU4_SHADOW_TRANSFER_SLICE_3 | XMC_CCU4_SHADOW_TRANSFER_PRESCALER_SLICE_3);

  /* Bind period match event to an NVIC node CCU40_1_IRQn */
  XMC_CCU4_SLICE_SetInterruptNode(CCU40_CC43, XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH, XMC_CCU4_SLICE_SR_ID_1);

  /* Enables timer(period match) event  */
  XMC_CCU4_SLICE_EnableEvent(CCU40_CC43, XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH);

  XMC_CCU4_SLICE_ClearTimer(CCU40_CC43);
  XMC_CCU4_SLICE_StartTimer(CCU40_CC43);

  //NVIC_SetPriority(CCU40_1_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),63,0));

  NVIC_EnableIRQ(CCU40_1_IRQn); //CCU40_3_IRQn


  while(1) {
    /* Infinite loop */
  }
}


void CCU40_1_IRQHandler(void) {
  XMC_GPIO_ToggleOutput(LED2);
  return;
}
