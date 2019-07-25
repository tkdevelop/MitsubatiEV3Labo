#include "ev3api.h"
#include "pid.h"
#include "colorsensor.h"

/*
 * PID���������\�b�h
 *
 * @param self �����̃|�C���^
 * @param threshold 臒l
 */
void Pid_init(Pid* self, int threshold) {
	self->threshold = threshold; /* 臒l������ */

	self->kp = 0.42; /* �Q�C�������� */
	self->ki = 0.06;
	self->kd = 0.027;

	self->delta = 0.004; /* ���������� */
}

/*
 * PID�擾���\�b�h
 *
 * @param self �����̃|�C���^
 * @return (p+i+d) PID
 */
float Pid_calc(Pid* self) {
	uint8_t reflect = ColorSensor_get_reflect(); /* ���ˌ��l�擾 */

	self->diff_prev = self->diff; /* �O��̕΍���ۑ� */
	self->diff = self->threshold - reflect; /* �΍����v�Z */
	
	/* PID�v�Z */
	int p = self->kp * self->diff;
	self->integral += ((self->diff + self->diff_prev) / 2.0) * self->delta;
	int i = self->ki * self->integral;
	int d = self->kd * (self->diff_prev - self->diff) / self->delta;

	return (p + i + d);
}