#ifndef _DISTANCE_H_
#define _DISTANCE_H_

typedef struct {
	float distance; /* ���s���� */
	float distance_4ms_left; /* ���^�C����4ms�Ԃ̋��� */
	float distance_4ms_right; /* �E�^�C����4ms�Ԃ̋��� */

	float pre_angle_left; /* �O��̍����[�^��]�p�x */
	float pre_angle_right; /* �O��̉E���[�^��]�p�x */
}Distance;
void Distance_init(Distance* self);
void Distance_update(Distance* self);
float Distance_get_distance(Distance* self);
float Distance_get_distance_4ms_right(Distance* self);
float Distance_get_distance_4ms_left(Distance* self);

#endif