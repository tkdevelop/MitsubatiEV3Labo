#include "Direction.h"

#define TREAD 195 /* �ԑ̃g���b�h�� */
#define PI 3.14159265358979 /* �~���� */

/*
 * ���ʌv���������\�b�h
 *
 * @param self �����̃|�C���^
 */
void Direction_init(Direction* self) {
	self->direction = 0.0;
}

/*
 * ���ʌv�Z���\�b�h
 *
 * @param self �����̃|�C���^
 * @return direction ����
 */
float Direction_calc(Direction* self, float distance_4ms_left, float distance_4ms_right) {
	self->direction += (360.0 / (2.0 * PI * TREAD)) * (distance_4ms_left - distance_4ms_right);
	return self->direction;
}

/*
 * ���ʃ��Z�b�g���\�b�h
 *
 * @param self �����̃|�C���^
 */
void Direction_reset(Direction* self) {
	self->direction = 0;
}