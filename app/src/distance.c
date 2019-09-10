#include "ev3api.h"
#include "distance.h"
#include "wheelmotor.h"

/* 左右モーターポート */
#define LEFT_MOTOR_P EV3_PORT_C
#define RIGHT_MOTOR_P EV3_PORT_B

#define TIRE_DISMETER 100.0 /* タイヤの直径 (100mm) */
#define PI 3.14159265358979 /* 円周率 */

/*
 * 距離計初期化メソッド
 *
 * @param self 自分のポインタ
 */
void Distance_init(Distance* self) {
	self->distance = 0.0;
	self->distance_4ms_left = 0.0;
	self->distance_4ms_right = 0.0;

	/* 左右モータの過去値に現在地を代入 */
	self->prev_angle_left = WheelMotor_get_angle(LEFT_MOTOR_P);
	self->prev_angle_right = WheelMotor_get_angle(RIGHT_MOTOR_P);
}

/*
 * 走行距離計算メソッド
 *
 * @param self 自分のポインタ
 * @return distance 走行距離
 */
float Distance_calc(Distance* self) {
	/* 左右モータの回転角度を取得 */
	float cur_angle_left = WheelMotor_get_angle(LEFT_MOTOR_P); 
	float cur_angle_right = WheelMotor_get_angle(RIGHT_MOTOR_P);

	float distance_4ms = 0.0; /* 4msの距離 */

	/* 左右モータの4ms間距離を計算 */
	self->distance_4ms_left = ((PI * TIRE_DISMETER) / 360.0) * (cur_angle_left - self->prev_angle_left);
	self->distance_4ms_right = ((PI * TIRE_DISMETER) / 360.0) * (cur_angle_right - self->prev_angle_right);
	distance_4ms = ((self->distance_4ms_left + self->distance_4ms_right) / 2.0); /* 4msの距離を計算 */
	self->distance += distance_4ms;

	/* モータの回転角殿過去値を更新 */
	self->prev_angle_left = cur_angle_left;
	self->prev_angle_right = cur_angle_right;

	return self->distance;
}

/*
 * 左タイヤの4ms間の走行距離取得メソッド
 *
 * @param self 自分のポインタ
 * @return distance_4ms_left 左タイヤの4ms間の走行距離
 */
float Distance_get_distance_4ms_left(Distance* self) {
	return self->distance_4ms_left;
}

/*
 * 右タイヤの4ms間の走行距離取得メソッド
 *
 * @param self 自分のポインタ
 * @return distance_4ms_right 右タイヤの4ms間の走行距離
 */
float Distance_get_distance_4ms_right(Distance* self){
	return self->distance_4ms_right;
}
