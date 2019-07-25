#include "ev3api.h"
#include "pid.h"
#include "colorsensor.h"

/*
 * PID初期化メソッド
 *
 * @param self 自分のポインタ
 * @param threshold 閾値
 */
void Pid_init(Pid* self, int threshold) {
	self->threshold = threshold; /* 閾値初期化 */

	self->kp = 0.78; /* ゲイン初期化 */
	self->ki = 0.06;
	self->kd = 0.027;

	self->delta = 0.004; /* 周期初期化 */
}

/*
 * PID取得メソッド
 *
 * @param self 自分のポインタ
 * @return (p+i+d) PID
 */
float Pid_calc(Pid* self) {
	uint8_t reflect = ColorSensor_get_reflect(); /* 反射光値取得 */

	self->diff_prev = self->diff; /* 前回の偏差を保存 */
	self->diff = self->threshold - reflect; /* 偏差を計算 */
	self->integral += ((self->diff + self->diff_prev) / 2.0) * self->delta;

	/* PID計算 */
	int p = self->kp * self->diff;
	int i = self->ki * self->integral;
	int d = self->kd * (self->diff - self->diff_prev) / self->delta;

	/*if (reflect < self->threshold) { //外回り
		return -20;
	}
	else {
		return 20;
	}*/

	/*if (reflect < self->threshold) { //内回り
		return 20;
	}
	else {
		return -20;
	}*/
	
	//return -(p + i + d); //外回り
	return (p + i + d); //内回り
}