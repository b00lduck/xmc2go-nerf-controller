#include "adc.h"
#include <xmc_vadc.h>


void initAdc() {
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
}

uint16_t adcGetPotBlocking() {
	  int globres = XMC_VADC_GLOBAL_GetDetailedResult(VADC);
	  while ((globres & 0x80000000) == 0); // Wait until new result write int the RESULT bits.
	  int group = (globres & 0xF0000) >> 16; // See which group happened the conversion.
	  int channel = (globres & 0x1F00000) >> 20; // See which channel happened the conversion.
	  int result = (globres & 0xFFFF) >> 2; // Store result in a variable.
	  return result;
}
