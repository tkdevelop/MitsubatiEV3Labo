#include "ev3api.h"
#include "clock.h"

/*
 * タイムリセットメソッド
 *
 * @param self 自分のポインタ
 */
void Clock_reset(Clock* self) {
	self->time = 0;
}

/*
 * タイムカウントアップメソッド
 *
 * @param self 自分のポインタ
 */
void Clock_time_countup(Clock* self) {
	self->time++;
}

/*
 * タイム取得メソッド
 *
 * @param self 自分のポインタ
 * @return time タイム
 */
int Clock_get_time(Clock* self) {
	return self->time;
}