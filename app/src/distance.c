#include "ev3api.h"
#include "distance.h"
#include "wheelmotor.h"

/* ���E���[�^�[�|�[�g */
#define LEFT_MOTOR_P EV3_PORT_C
#define RIGHT_MOTOR_P EV3_PORT_B

#define TIRE_DISMETER 100.0 /* �^�C���̒��a (100mm) */
#define PI 3.14159265358979 /* �~���� */

/*
 * �����v���������\�b�h
 *
 * @param self �����̃|�C���^
 */
void Distance_init(Distance* self) {
	self->distance = 0.0;
	self->distance_4ms_left = 0.0;
	self->distance_4ms_right = 0.0;

	/* ���E���[�^�̉ߋ��l�Ɍ��ݒn���� */
	self->prev_angle_left = WheelMotor_get_angle(LEFT_MOTOR_P);
	self->prev_angle_right = WheelMotor_get_angle(RIGHT_MOTOR_P);
}

/*
 * ���s�����v�Z���\�b�h
 *
 * @param self �����̃|�C���^
 * @return distance ���s����
 */
float Distance_calc(Distance* self) {
	/* ���E���[�^�̉�]�p�x���擾 */
	float cur_angle_left = WheelMotor_get_angle(LEFT_MOTOR_P); 
	float cur_angle_right = WheelMotor_get_angle(RIGHT_MOTOR_P);

	float distance_4ms = 0.0; /* 4ms�̋��� */

	/* ���E���[�^��4ms�ԋ������v�Z */
	self->distance_4ms_left = ((PI * TIRE_DISMETER) / 360.0) * (cur_angle_left - self->prev_angle_left);
	self->distance_4ms_right = ((PI * TIRE_DISMETER) / 360.0) * (cur_angle_right - self->prev_angle_right);
	distance_4ms = ((self->distance_4ms_left + self->distance_4ms_right) / 2.0); /* 4ms�̋������v�Z */
	self->distance += distance_4ms;

	/* ���[�^�̉�]�p�a�ߋ��l���X�V */
	self->prev_angle_left = cur_angle_left;
	self->prev_angle_right = cur_angle_right;

	return self->distance;
}

/*
 * ���^�C����4ms�Ԃ̑��s�����擾���\�b�h
 *
 * @param self �����̃|�C���^
 * @return distance_4ms_left ���^�C����4ms�Ԃ̑��s����
 */
float Distance_get_distance_4ms_left(Distance* self) {
	return self->distance_4ms_left;
}

/*
 * �E�^�C����4ms�Ԃ̑��s�����擾���\�b�h
 *
 * @param self �����̃|�C���^
 * @return distance_4ms_right �E�^�C����4ms�Ԃ̑��s����
 */
float Distance_get_distance_4ms_right(Distance* self){
	return self->distance_4ms_right;
}
