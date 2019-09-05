#include "ev3api.h"
#include "clock.h"

/*
 * �^�C�����Z�b�g���\�b�h
 *
 * @param self �����̃|�C���^
 */
void Clock_reset(Clock* self) {
	self->time = 0;
}

/*
 * �^�C���J�E���g�A�b�v���\�b�h
 *
 * @param self �����̃|�C���^
 */
void Clock_time_countup(Clock* self) {
	self->time++;
}

/*
 * �^�C���擾���\�b�h
 *
 * @param self �����̃|�C���^
 * @return time �^�C��
 */
int Clock_get_time(Clock* self) {
	return self->time;
}