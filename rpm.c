#include <stdint.h>
#include "rpm.h"
#include "config.h"
#include "pwm.h"

uint16_t motor1_rpm = 0;
uint16_t motor2_rpm = 0;

uint16_t motor1_rotation_time = 0;
uint16_t motor2_rotation_time = 0;

uint8_t old_tach1 = 0;
uint8_t old_tach2 = 0;

uint8_t stalled = 0;


