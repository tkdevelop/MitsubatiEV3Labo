#include "ev3api.h"
#include "leftmotor.h"

#define LEFT_MOTOR_P EV3_PORT_C /* 左モータポート */

/*
 * 左モータリセットメソッド
 */
void LeftMotor_reset() {
	ev3_motor_reset_counts(LEFT_MOTOR_P);
}

/*
 * 左モータ回転角度取得メソッド
 *
 * return angle 回転角度
 */
int32_t LeftMotor_get_angle() {
	int32_t angle = ev3_motor_get_counts(LEFT_MOTOR_P);
	return angle;
}

/*
 * 左タイヤモータ出力制御
 */
void LeftMotor_set_tire_motor(int8_t pwm) {
	if (0x00 == pwm)
	{
		/* PWMが0である場合、モータ停止 */
		ev3_motor_stop(LEFT_MOTOR_P, true);
	}
	else
	{
		/* モータ出力 */
		ev3_motor_set_power(LEFT_MOTOR_P, (int)pwm);
	}
}