#pragma once

void initPwm();

void initMotor1();
void enableMotor1(float speed);
void disableMotor1();

void initMotor2();
void enableMotor2(float speed);
void disableMotor2();

void initMotor3();
void enableMotor3(float speed);
void disableMotor3();

extern uint8_t motor1enabled;
extern uint8_t motor2enabled;
extern uint8_t motor3enabled;
