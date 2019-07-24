#include "ev3api.h"
#include "leftmotor.h"

#define RIGHT_MOTOR_P EV3_PORT_B /* 右モーターポート */

/*
 * 左モーターリセットメソッド
 */
void RightMotor_reset() {
	ev3_motor_reset_counts(RIGHT_MOTOR_P);
}

/*
 * 左モーター回転角度取得メソッド
 *
 * return angle 回転角度
 */
int32_t RightMotor_get_angle() {
	int32_t angle = ev3_motor_get_counts(RIGHT_MOTOR_P);
	return angle;
}