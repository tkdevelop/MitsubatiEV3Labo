#include "ev3api.h"
#include "runningstyle.h"
#include "linetrace.h"
#include "pidcontrol.h"

/*
 * 走法クラス初期化メソッド
 *
 * @param self 自分のポインタ
 * @param pidControl PID制御クラスのポインタ
 */
void RunningStyle_init(RunningStyle* self, Linetrace* linetrace, PidControl* pidControl) {
	self->linetrace = linetrace; /* 走行くらうポインタ格納 */
	self->pidControl = pidControl; /* PID制御クラスポインタ格納 */
}

/*
 * 走法切り替えメソッド
 *
 * @param self 自分のポインタ
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