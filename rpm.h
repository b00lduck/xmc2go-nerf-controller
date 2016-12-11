#pragma once
#include <stdint.h>
#include "config.h"
#include "pwm.h"

extern uint16_t motor1_rpm;
extern uint16_t motor2_rpm;

extern uint16_t motor1_rotation_time;
extern uint16_t motor2_rotation_time;

extern uint8_t stalled;

void initRpm();

static inline uint16_t getMotor1Rpm() {
	return motor1_rpm;
}

static inline uint16_t getMotor2Rpm() {
	return motor2_rpm;
}

static inline void advanceRpmCounter() {
	motor1_rotation_time ++;
	motor2_rotation_time ++;
}

static inline void stall() {
	motor1_rotation_time = 0;
	motor1_rpm = 0;
	motor2_rotation_time = 0;
	motor2_rpm = 0;
	stalled = 1;
	disableMotor1();
	disableMotor2();
}

static inline void unStall() {
  stalled = 0;
  disableMotor1();
  disableMotor2();
}

static inline void regulateRotors(uint16_t desired_rpm) {

	if (desired_rpm < 500) {
		unStall();
    } else if (((motor1_rotation_time >= SYSTICKS_PER_SECOND) ||
    	  (motor2_rotation_time >= SYSTICKS_PER_SECOND)) &&
		(desired_rpm > 1500)) {
      stall();
	}

  	if (!stalled) {
		float output1 = 0.0001 * (desired_rpm - motor1_rpm);
		float output2 = 0.0001 * (desired_rpm - motor2_rpm);
		enableMotor1(output1);
		enableMotor2(output2);
  	}

}
