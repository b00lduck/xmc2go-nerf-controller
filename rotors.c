#include <stdint.h>
#include "config.h"
#include "pwm.h"
#include "rotors.h"

uint16_t motor1_rpm = 0;
uint16_t motor2_rpm = 0;

uint32_t motor1_rotation_time = 0;
uint32_t motor2_rotation_time = 0;

uint8_t old_tach1 = 0;
uint8_t old_tach2 = 0;

uint8_t rotors_stalled = 0;

uint8_t old_rotor_state = 0;


