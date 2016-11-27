#include <xmc_ccu4.h>
#include <xmc_gpio.h>
#include <xmc_scu.h>
#include <xmc1_scu.h>
#include <xmc_vadc.h>
#include "pwm.h"

#include "config.h"



int _init(void) {}


int main(void) {
  XMC_GPIO_SetMode(LED1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(LED2, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(MOTOR1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(MOTOR2, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(MOTOR2_BRAKE, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);

  XMC_GPIO_SetOutputLow(LED1);
  XMC_GPIO_SetOutputLow(LED2);
  XMC_GPIO_SetOutputLow(MOTOR1);
  XMC_GPIO_SetOutputLow(MOTOR2);
  XMC_GPIO_SetOutputLow(MOTOR2_BRAKE);

  XMC_GPIO_SetMode(BUTTON1, XMC_GPIO_MODE_INPUT_PULL_UP);
  XMC_GPIO_SetMode(BUTTON2, XMC_GPIO_MODE_INPUT_PULL_UP);
  XMC_GPIO_SetMode(BUTTON3, XMC_GPIO_MODE_INPUT_PULL_UP);

  XMC_GPIO_EnableDigitalInput(BUTTON1);
  XMC_GPIO_EnableDigitalInput(BUTTON2);
  XMC_GPIO_EnableDigitalInput(BUTTON3);


  /* System timer configuration */
  SysTick_Config(SystemCoreClock >> 6);


  XMC_SCU_CLOCK_CONFIG_t clock_config = {
		  .pclk_src = XMC_SCU_CLOCK_PCLKSRC_DOUBLE_MCLK,
		  .rtc_src = XMC_SCU_CLOCK_RTCCLKSRC_DCO2,
		  .fdiv = 0,
		  .idiv = 1,
  };

  /* Ensure clock frequency is set at 64MHz (2*MCLK) */
  XMC_SCU_CLOCK_Init(&clock_config);

  initPwm();


  // *******************
  // ADC
  // *******************


  XMC_VADC_GLOBAL_CONFIG_t adc_glob_handl = {
		  .class1 = {
				  .conversion_mode_standard = XMC_VADC_CONVMODE_8BIT,
				  .sample_time_std_conv = 3,
		  }
  };

  XMC_VADC_CHANNEL_CONFIG_t adc_ch_handl = {
		  .alias_channel=-1,
		  .input_class=XMC_VADC_CHANNEL_CONV_GROUP_CLASS1,
		  .result_reg_number=7,
		  .result_alignment=XMC_VADC_RESULT_ALIGN_RIGHT,
  };

  XMC_VADC_SCAN_CONFIG_t adc_bg_handl={
		  .conv_start_mode= XMC_VADC_STARTMODE_WFS,
  };

  XMC_VADC_GLOBAL_Init(VADC, &adc_glob_handl);
  XMC_VADC_GLOBAL_StartupCalibration(VADC);
  XMC_VADC_GLOBAL_BackgroundInit(VADC, &adc_bg_handl) ;
  XMC_VADC_GLOBAL_BackgroundAddChannelToSequence(VADC, 0, 0);
  XMC_VADC_GLOBAL_BackgroundEnableContinuousMode(VADC);
  XMC_VADC_GLOBAL_BackgroundTriggerConversion(VADC);

  XMC_CCU4_SLICE_SetTimerCompareMatch(SLICE0_PTR, 62499U);


  while(1) {

	  int globres = XMC_VADC_GLOBAL_GetDetailedResult(VADC);

	  while ((globres & 0x80000000) == 0); // Wait until new result write int the RESULT bits.
	  int group = (globres & 0xF0000) >> 16; // See which group happened the conversion.
	  int channel = (globres & 0x1F00000) >> 20; // See which channel happened the conversion.
	  int result = (globres & 0xFFFF) >> 2; // Store result in a variable.

	  XMC_CCU4_SLICE_SetTimerCompareMatch(SLICE0_PTR, 55000U - (result * 30));
	  XMC_CCU4_EnableShadowTransfer(MODULE_PTR, (uint32_t)(XMC_CCU4_SHADOW_TRANSFER_SLICE_0|XMC_CCU4_SHADOW_TRANSFER_PRESCALER_SLICE_0));

  }

}

uint8_t pusher_active = 0;
uint8_t pusher_timer = 0;

void SysTick_Handler(void) {
  XMC_GPIO_ToggleOutput(LED1);

  int rotors = XMC_GPIO_GetInput(BUTTON1);
  if (rotors != 1) {
	  enableMotor1();
  } else {
	  disableMotor1();
  }


  int trigger = XMC_GPIO_GetInput(BUTTON2);
  int trigger_hold = XMC_GPIO_GetInput(BUTTON3);

  if (!trigger > 0) {
	  pusher_active = 1;
  }

  if (pusher_active == 1) {
	  pusher_timer++;
  } else {
	  pusher_timer = 0;
	  disableMotor2();
  }

  if (pusher_active && pusher_timer < 10) {
	  enableMotor2(40000);
  } else if (!trigger_hold) {
	  enableMotor2(55000);
  } else {
	  pusher_active = 0;
	  pusher_timer = 0;
	  disableMotor2();
  }

}

void CCU40_1_IRQHandler(void) {
  XMC_GPIO_ToggleOutput(LED2);
  return;
}
