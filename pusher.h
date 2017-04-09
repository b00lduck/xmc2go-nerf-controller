#pragma once
#include <stdint.h>
#include <xmc_gpio.h>
#include "config.h"
#include "pwm.h"

extern uint8_t pusher_stalled;
extern uint32_t pusher_counter;
extern uint8_t pusher_state;

static inline void advancePusherCounter() {
	pusher_counter++;

	if (pusher_counter > SYSTICKS_PER_SECOND) {
		pusher_stalled = 1;
	}
}

static inline void processPusher(uint8_t pusher_mode, uint8_t ammo_ready) {

	uint8_t trigger = !XMC_GPIO_GetInput(BUTTON2);
	uint8_t trigger_hold = !XMC_GPIO_GetInput(BUTTON1);

	if (pusher_mode) {
		XMC_GPIO_SetOutputHigh(LED_YELLOW);
	} else {
		XMC_GPIO_SetOutputLow(LED_YELLOW);
	}

	if (!ammo_ready) {
		XMC_GPIO_SetOutputHigh(LED_ORANGE);
	} else {
		XMC_GPIO_SetOutputLow(LED_ORANGE);
	}

	switch (pusher_state) {

	  	// State 0: resting in "zero" position
		case 0:
			if (trigger_hold) {
				pusher_state = 5;
			}
			pusher_counter = 0;
			disableMotor3();
			if ((trigger) && (ammo_ready)) {
				pusher_state = 1;
			}
			break;

		// State 1: shot requested
		case 1:
			enableMotor3(1);
			if (trigger_hold) {
				if (pusher_mode == 0) {
					pusher_state = 2;
				} else {
					pusher_state = 4;
				}
			}
			break;

		// State 2: shot in progress (single mode)
		case 2:
			enableMotor3(PUSHER_POWER_SINGLE);
			if (!trigger_hold) {
				pusher_state = 3;
			}
			break;

		// State 3: shot done, waiting for trigger cycle (single mode)
		case 3:
			disableMotor3();
			if (!trigger) {
				pusher_state = 0;
			}
			break;

		// State 4: shot in progress (full auto mode)
		case 4:
			enableMotor3(PUSHER_POWER_FULL);
			if (!trigger || !ammo_ready) {
				pusher_state = 5;
			}
			break;

		// State 5: wait for end of full auto shot
		case 5:
			enableMotor3(PUSHER_POWER_RETURN);
			if (!trigger_hold) {
				pusher_state = 0;
			}
			break;

	}
}
