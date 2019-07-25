#include "ev3api.h"
#include "leftmotor.h"

#define LEFT_MOTOR_P EV3_PORT_C /* �����[�^�|�[�g */

/*
 * �����[�^���Z�b�g���\�b�h
 */
void LeftMotor_reset() {
	ev3_motor_reset_counts(LEFT_MOTOR_P);
}

/*
 * �����[�^��]�p�x�擾���\�b�h
 *
 * return angle ��]�p�x
 */
int32_t LeftMotor_get_angle() {
	int32_t angle = ev3_motor_get_counts(LEFT_MOTOR_P);
	return angle;
}

/*
 * ���^�C�����[�^�o�͐���
 */
void LeftMotor_set_tire_motor(int8_t pwm) {
	if (0x00 == pwm)
	{
		/* PWM��0�ł���ꍇ�A���[�^��~ */
		ev3_motor_stop(LEFT_MOTOR_P, true);
	}
	else
	{
		/* ���[�^�o�� */
		ev3_motor_set_power(LEFT_MOTOR_P, (int)pwm);
	}
}