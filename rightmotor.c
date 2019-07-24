#include "ev3api.h"
#include "leftmotor.h"

#define RIGHT_MOTOR_P EV3_PORT_B /* �E���[�^�[�|�[�g */

/*
 * �����[�^�[���Z�b�g���\�b�h
 */
void RightMotor_reset() {
	ev3_motor_reset_counts(RIGHT_MOTOR_P);
}

/*
 * �����[�^�[��]�p�x�擾���\�b�h
 *
 * return angle ��]�p�x
 */
int32_t RightMotor_get_angle() {
	int32_t angle = ev3_motor_get_counts(RIGHT_MOTOR_P);
	return angle;
}