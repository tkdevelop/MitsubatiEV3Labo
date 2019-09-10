#include "Direction.h"

#define TREAD 195 /* 車体トレッド幅 */
#define PI 3.14159265358979 /* 円周率 */

/*
 * 方位計初期化メソッド
 *
 * @param self 自分のポインタ
 */
void Direction_init(Direction* self) {
	self->direction = 0.0;
}

/*
 * 方位計算メソッド
 *
 * @param self 自分のポインタ
 * @return direction 方位
 */
float Direction_calc(Direction* self, float distance_4ms_left, float distance_4ms_right) {
	self->direction += (360.0 / (2.0 * PI * TREAD)) * (distance_4ms_left - distance_4ms_right);
	return self->direction;
}

/*
 * 方位リセットメソッド
 *
 * @param self 自分のポインタ
 */
void Direction_reset(Direction* self) {
	self->direction = 0;
}