#include "ev3api.h"
#include "distance.h"

/* ���E���[�^�[�|�[�g */
#define LEFT_MOTOR_P LEFT_MOTOR
#define RIGHT_MOTOR_P RIGHT_MOTOR

/*
 * ���Ȉʒu���菉�������\�b�h
 *
 * @param self �����̃|�C���^
 */
void Distance_init(Distance* self) {
	self-> pre
}

/*
 * �����X�V���\�b�h
 *
 * @param self �����̃|�C���^
 */
void Distance_update(Distance* self) {

}

/*
 * ���s�����擾���\�b�h
 *
 * @param self �����̃|�C���^
 * return distance ���s���� 
 */
float Distance_get_distance(Distance* self) {
	return 0;
}

/*
 * ���^�C����4ms�Ԃ̋����擾���\�b�h
 *
 * @param self �����̃|�C���^
 * return distance_4ms_left ���^�C����4ms�Ԃ̋���
 */
float Distance_get_distance_4ms_left(Distance* self) {
	return 0;
}

/*
 * �E�^�C����4ms�ԋ����擾���\�b�h
 *
 * @param self �����̃|�C���^
 * return distance_4ms_right �E�^�C����4ms�Ԃ̋���
 */
float Distance_get_distance_4ms_right(Distance* self) {
	return 0;
}
