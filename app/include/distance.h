#ifndef _DISTANCE_H_
#define _DISTANCE_H_

typedef struct {
	float distance; /* ���s���� */

	float preAngleLeft; /* �O��̍����[�^��]�p�x */
	float preAngleRight; /* �O��̉E���[�^��]�p�x */
}Distance;
void Distance_init(Distance* self);
void Distance_update(Distance* self);
void Distance_get_distance();

#endif