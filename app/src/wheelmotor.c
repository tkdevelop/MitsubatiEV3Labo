#include "ev3api.h"
#include "wheelmotor.h"

/*
 * ���[�^���Z�b�g���\�b�h
 */
void WheelMotor_reset(int motor_port) {
	ev3_motor_reset_counts(motor_port);
}

/*
 * ���[�^��]�p�x�擾���\�b�h
 *
 * return angle ��]�p�x
 */
int32_t WheelMotor_get_angle(int motor_port) {
	int32_t angle = ev3_motor_get_counts(motor_port);
	return angle;
}

/*
 * ���[�^�o�͐���
 */
void WheelMotor_set_tire_motor(int motor_port,int8_t pwm) {
	if (0x00 == pwm)
	{
		/* PWM��0�ł���ꍇ�A���[�^��~ */
		ev3_motor_stop(motor_port, true);
	}
	else
	{
		/* ���[�^�o�� */
		ev3_motor_set_power(motor_port, (int)pwm);
	}
}