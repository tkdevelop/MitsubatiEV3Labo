#include "ev3api.h"
#include "leftmotor.h"

#define LEFT_MOTOR_P EV3_PORT_C

/*
 * 左モーターリセットメソッド
 */
void LeftMotor_reset() {
	ev3_motor_reset_counts(LEFT_MOTOR_P);
}

/*
 * 左モーター回転角度取得メソッド
 *
 * return angle 回転角度
 */
int32_t LeftMotor_get_angle() {
	int32_t angle = ev3_motor_get_counts(LEFT_MOTOR_P);
	return angle;
}