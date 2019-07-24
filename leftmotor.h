#ifndef _LEFTMOTOR_H_
#define _LEFTMOTOR_H_

void LeftMotor_reset();
int32_t LeftMotor_get_angle();
void LeftMotor_set_tire_motor(int8_t pwm);

#endif