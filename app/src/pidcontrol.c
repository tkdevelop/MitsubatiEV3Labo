#include "ev3api.h"
#include "pidcontrol.h"
#include "colorsensor.h"

/*
 * PID制御初期化メソッド
 *
 * @param self 自分のポインタ
 * @param threshold 閾値
 */
void PidControl_init(PidControl* self, int threshold) {
	self->kp = 0; /* ゲイン初期化 */
	self->ki = 0;
	self->kd = 0;

	self->delta = 0.004; /* 周期初期化 */

	self->diff = 0.0; /* 偏差初期化 */
	self->prev_diff = 0.0;

	self->threshold = threshold; /* 閾値初期化 */
}

/*
 * PID取得メソッド
 *
 * @param self 自分のポインタ
 * @return (p+i+d) PID
 */
float PidControl_calc(PidControl* self) {
	uint8_t reflect = ColorSensor_get_reflect(); /* 反射光値取得 */

	self->prev_diff = self->diff; /* 前回の偏差を保存 */
	self->diff = self->threshold - reflect; /* 偏差を計算 */
	self->integral += ((self->diff + self->prev_diff) / 2.0) * self->delta;

	/* PID計算 */
	int p = self->kp * self->diff;
	int i = self->ki * self->integral;
	int d = self->kd * (self->diff - self->prev_diff) / self->delta;

	return (p + i + d);
}