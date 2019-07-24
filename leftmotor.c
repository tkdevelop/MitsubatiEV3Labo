#include "ev3api.h"
#include "leftmotor.h"

#define LEFT_MOTOR_P EV3_PORT_C

/*
 * �����[�^�[���Z�b�g���\�b�h
 */
void LeftMotor_reset() {
	ev3_motor_reset_counts(LEFT_MOTOR_P);
}

/*
 * �����[�^�[��]�p�x�擾���\�b�h
 *
 * return angle ��]�p�x
 */
int32_t LeftMotor_get_angle() {
	int32_t angle = ev3_motor_get_counts(LEFT_MOTOR_P);
	return angle;
}