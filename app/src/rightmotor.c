#include "ev3api.h"
#include "leftmotor.h"

#define RIGHT_MOTOR_P EV3_PORT_B /* �E���[�^�|�[�g */

/*
 * �E���[�^���Z�b�g���\�b�h
 */
void RightMotor_reset() {
	ev3_motor_reset_counts(RIGHT_MOTOR_P);
}

/*
 * �E���[�^��]�p�x�擾���\�b�h
 *
 * return angle ��]�p�x
 */
int32_t RightMotor_get_angle() {
	int32_t angle = ev3_motor_get_counts(RIGHT_MOTOR_P);
	return angle;
}

/*
 * �E�^�C�����[�^�o�͐���
 */
void RightMotor_set_tire_motor(int8_t pwm) {
	if (0x00 == pwm)
	{
		/* PWM��0�ł���ꍇ�A���[�^��~ */
		ev3_motor_stop(RIGHT_MOTOR_P, true);
	}
	else
	{
		/* ���[�^�o�� */
		ev3_motor_set_power(RIGHT_MOTOR_P, (int)pwm);
	}
}