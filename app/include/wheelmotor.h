#ifndef _WHEELMOTOR_H_
#define _WHEELMOTOR_H_

void WheelMotor_reset(int motor_port);
int32_t WheelMotor_get_angle(int motor_port);
void WheelMotor_set_tire_motor(int motor_port, int8_t pwm);

#endif