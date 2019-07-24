#ifndef _RIGHTMOTOR_H_
#define _RIGHTMOTOR_H_

void RightMotor_reset();
int32_t RightMotor_get_angle();
void RightMotor_set_tire_motor(int8_t pwm);

#endif