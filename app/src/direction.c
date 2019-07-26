#include "ev3api.h"
#include "direction.h"
#include "distance.h"

#define TREAD 175.0 /* �ԑ̃g���b�h�� (175.0mm) */
#define PI 3.14159265358979 /* �~���� */

/*
 * ���ʌ`���������\�b�h
 *
 * @param self �����̃|�C���^
 */
void Direction_init(Direction* self,Distance* distance) {
	self->distance = distance; /* �����v�|�C���^�i�[ */

	self->direction = 0.0; /* ���ʏ����� */
}

/*
 * ���ʍX�V���\�b�h
 *
 * @param self �����̃|�C���^
 */
void Direction_update(Direction* self) {
	/* ���ʌv�Z */
	self->direction += (360.0 / (2.0 * PI * TREAD)) * (Distance_get_distance_4ms_left(self->distance) - Distance_get_distance_4ms_right(self->distance));
}

/*
 * ���ʎ擾���\�b�h
 *
 * @param self �����̃|�C���^
 * return direction ����
 */
float Direction_get_direction(Direction* self) {
	return self->direction;
}