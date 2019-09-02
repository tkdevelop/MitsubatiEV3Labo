#include "ev3api.h"
#include "pidcontrol.h"
#include "colorsensor.h"

/*
 * PID���䏉�������\�b�h
 *
 * @param self �����̃|�C���^
 * @param threshold 臒l
 */
void PidControl_init(PidControl* self, int threshold) {
	self->kp = 0; /* �Q�C�������� */
	self->ki = 0;
	self->kd = 0;

	self->delta = 0.004; /* ���������� */

	self->diff = 0.0; /* �΍������� */
	self->prev_diff = 0.0;

	self->threshold = threshold; /* 臒l������ */
}

/*
 * PID�擾���\�b�h
 *
 * @param self �����̃|�C���^
 * @return (p+i+d) PID
 */
float PidControl_calc(PidControl* self) {
	uint8_t reflect = ColorSensor_get_reflect(); /* ���ˌ��l�擾 */

	self->prev_diff = self->diff; /* �O��̕΍���ۑ� */
	self->diff = self->threshold - reflect; /* �΍����v�Z */
	self->integral += ((self->diff + self->prev_diff) / 2.0) * self->delta;

	/* PID�v�Z */
	int p = self->kp * self->diff;
	int i = self->ki * self->integral;
	int d = self->kd * (self->diff - self->prev_diff) / self->delta;

	return (p + i + d);
}