#include "adc.h"
#include <xmc_vadc.h>


void initAdc() {
	  XMC_VADC_GLOBAL_CONFIG_t adc_glob_handl = {
			  .class1 = {
					  .conversion_mode_standard = XMC_VADC_CONVMODE_8BIT,
					  .sample_time_std_conv = 1,
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
	  XMC_VADC_GLOBAL_BackgroundAddChannelToSequence(VADC, 0, 2);
	  XMC_VADC_GLOBAL_BackgroundEnableContinuousMode(VADC);
	  XMC_VADC_GLOBAL_BackgroundTriggerConversion(VADC);
}

void adcProcess(float *pot, int *battery) {
	int adc_globres = XMC_VADC_GLOBAL_GetDetailedResult(VADC);
	while ((adc_globres & 0x80000000) == 0);
	int channel = (adc_globres & 0x1F00000) >> 20;
	int result = (adc_globres & 0xFFFF) >> 2;
	if (channel == 0) {
		*pot = (float)result / 1024.0;
	} else if (channel == 2) {
		*battery = result;
	}
}
