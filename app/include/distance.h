#ifndef _DISTANCE_H_
#define _DISTANCE_H_

typedef struct {
	float distance; /* ���s���� */
	float distance4msL; /* ���^�C����4ms�Ԃ̋��� */
	float distance4msR; /* �E�^�C����4ms�Ԃ̋��� */

	float preAngleLeft; /* �O��̍����[�^��]�p�x */
	float preAngleRight; /* �O��̉E���[�^��]�p�x */
}Distance;
void Distance_init(Distance* self);
void Distance_update(Distance* self);
float Distance_get_distance(Distance* self);
float Distance_get_distance_4ms_right(Distance* self);
float Distance_get_distance_4ms_left(Distance* self);

#endif