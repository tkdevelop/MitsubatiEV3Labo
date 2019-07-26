#include "ev3api.h"
#include "distance.h"

/* 左右モーターポート */
#define LEFT_MOTOR_P LEFT_MOTOR
#define RIGHT_MOTOR_P RIGHT_MOTOR

/*
 * 自己位置推定初期化メソッド
 *
 * @param self 自分のポインタ
 */
void Distance_init(Distance* self) {
	self-> pre
}

/*
 * 距離更新メソッド
 *
 * @param self 自分のポインタ
 */
void Distance_update(Distance* self) {

}

/*
 * 走行距離取得メソッド
 *
 * @param self 自分のポインタ
 * return distance 走行距離 
 */
float Distance_get_distance(Distance* self) {
	return 0;
}

/*
 * 左タイヤの4ms間の距離取得メソッド
 *
 * @param self 自分のポインタ
 * return distance_4ms_left 左タイヤの4ms間の距離
 */
float Distance_get_distance_4ms_left(Distance* self) {
	return 0;
}

/*
 * 右タイヤの4ms間距離取得メソッド
 *
 * @param self 自分のポインタ
 * return distance_4ms_right 右タイヤの4ms間の距離
 */
float Distance_get_distance_4ms_right(Distance* self) {
	return 0;
}
