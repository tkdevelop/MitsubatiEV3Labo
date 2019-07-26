#include "ev3api.h"
#include "direction.h"
#include "distance.h"

#define TREAD 175.0 /* 車体トレッド幅 (175.0mm) */
#define PI 3.14159265358979 /* 円周率 */

/*
 * 方位形初期化メソッド
 *
 * @param self 自分のポインタ
 */
void Direction_init(Direction* self,Distance* distance) {
	self->distance = distance; /* 距離計ポインタ格納 */

	self->direction = 0.0; /* 方位初期化 */
}

/*
 * 方位更新メソッド
 *
 * @param self 自分のポインタ
 */
void Direction_update(Direction* self) {
	/* 方位計算 */
	self->direction += (360.0 / (2.0 * PI * TREAD)) * (Distance_get_distance_4ms_left(self->distance) - Distance_get_distance_4ms_right(self->distance));
}

/*
 * 方位取得メソッド
 *
 * @param self 自分のポインタ
 * return direction 方位
 */
float Direction_get_direction(Direction* self) {
	return self->direction;
}