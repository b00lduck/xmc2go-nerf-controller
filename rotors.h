#pragma once
#include <stdint.h>
#include <xmc_gpio.h>
#include "config.h"
#include "pwm.h"
#include "adc.h"

extern uint16_t motor1_rpm;
extern uint16_t motor2_rpm;

extern uint32_t motor1_rotation_time;
extern uint32_t motor2_rotation_time;

extern uint8_t rotors_stalled;

extern uint8_t old_tach1;
extern uint8_t old_tach2;

extern uint8_t old_rotor_state;

static inline void advanceRotorsCounter() {
	if (motor1enabled) {
		motor1_rotation_time ++;
		uint8_t tach1 = XMC_GPIO_GetInput(MOTOR1_TACHOMETER);
		if (tach1 != old_tach1) {
			motor1_rpm = (float)SYSTICKS_PER_MINUTE / (float)motor1_rotation_time;
			motor1_rotation_time = 0;
			old_tach1 = tach1;
		}
	}

	if (motor2enabled) {
		motor2_rotation_time ++;
		uint8_t tach2 = XMC_GPIO_GetInput(MOTOR2_TACHOMETER);
		if (tach2 != old_tach2) {
			motor2_rpm = (float)SYSTICKS_PER_MINUTE / (float)motor2_rotation_time;
			motor2_rotation_time = 0;
			old_tach2 = tach2;
		}
	}
}

static inline void resetRotors() {
	motor1_rotation_time = 0;
	motor1_rpm = 0;
	motor2_rotation_time = 0;
	motor2_rpm = 0;
	disableMotor1();
	disableMotor2();
}

static inline void stallRotors() {
	rotors_stalled = 1;
	resetRotors();
}

static inline void regulateRotors(uint16_t desired_rpm) {
	// stall detection
	if (desired_rpm > 0) {
		if ((motor1_rotation_time >= SYSTICKS_PER_SECOND) || (motor2_rotation_time >= SYSTICKS_PER_SECOND)) {
			stallRotors();
		}
	  	if (!rotors_stalled) {
			float output1 = 0.0001 * (desired_rpm - motor1_rpm);
			float output2 = 0.0001 * (desired_rpm - motor2_rpm);
			enableMotor1(output1);
			enableMotor2(output2);
	  	}
	} else {
		resetRotors();
	}
}

static inline void processRotors(float desired_rpm, uint8_t ammo_ready) {
	uint8_t rotors = XMC_GPIO_GetInput(BUTTON3);
	if (old_rotor_state != rotors) {
		old_rotor_state = rotors;
		resetRotors();
	}
	if ((rotors != 1) && (ammo_ready)) {
		regulateRotors(desired_rpm);
	} else {
		regulateRotors(0);
	}
}
