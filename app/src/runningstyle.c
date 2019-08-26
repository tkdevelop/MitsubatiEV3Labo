#include "ev3api.h"
#include "runningstyle.h"
#include "linetrace.h"
#include "pidcontrol.h"

/*
 * ���@�N���X���������\�b�h
 *
 * @param self �����̃|�C���^
 * @param pidControl PID����N���X�̃|�C���^
 */
void RunningStyle_init(RunningStyle* self, Linetrace* linetrace, PidControl* pidControl) {
	self->linetrace = linetrace; /* ���s���炤�|�C���^�i�[ */
	self->pidControl = pidControl; /* PID����N���X�|�C���^�i�[ */
}

/*
 * ���@�؂�ւ����\�b�h
 *
 * @param self �����̃|�C���^
 */
void RunningStyle_switch(RunningStyle* self, int scene) {
	switch (scene) {
	case 0:
		self->linetrace->forward = 90;
		self->pidControl->kp = 0.80;
		self->pidControl->ki = 0.06;
		self->pidControl->kd = 0.025;
		break;
	case 1:
		self->linetrace->forward = 90;
		self->pidControl->kp = 0.80;
		self->pidControl->ki = 0.06;
		self->pidControl->kd = 0.025;
		break;
	case 2:
		self->linetrace->forward = 90;
		self->pidControl->kp = 0.80;
		self->pidControl->ki = 0.06;
		self->pidControl->kd = 0.025;
		break;
	case 3:
		self->linetrace->forward = 90;
		self->pidControl->kp = 0.80;
		self->pidControl->ki = 0.06;
		self->pidControl->kd = 0.025;
		break;
	case 4:
		self->linetrace->forward = 90;
		self->pidControl->kp = 0.80;
		self->pidControl->ki = 0.06;
		self->pidControl->kd = 0.025;
		break;
	default:
		self->linetrace->forward = 90;
		self->pidControl->kp = 0.80;
		self->pidControl->ki = 0.06;
		self->pidControl->kd = 0.025;
		break;
	}
}