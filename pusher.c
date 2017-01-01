#include <stdint.h>
#include "pusher.h"
#include "config.h"
#include "pwm.h"

uint8_t pusher_stalled = 0;
uint32_t pusher_counter = 0;
uint8_t pusher_state = 0;
