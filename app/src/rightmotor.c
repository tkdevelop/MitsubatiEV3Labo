#include "ev3api.h"
#include "leftmotor.h"

#define RIGHT_MOTOR_P EV3_PORT_B /* 右モータポート */

/*
 * 右モータリセットメソッド
 */
void RightMotor_reset() {
	ev3_motor_reset_counts(RIGHT_MOTOR_P);
}

/*
 * 右モータ回転角度取得メソッド
 *
 * return angle 回転角度
 */
int32_t RightMotor_get_angle() {
	int32_t angle = ev3_motor_get_counts(RIGHT_MOTOR_P);
	return angle;
}

/*
 * 右タイヤモータ出力制御
 */
void RightMotor_set_tire_motor(int8_t pwm) {
	if (0x00 == pwm)
	{
		/* PWMが0である場合、モータ停止 */
		ev3_motor_stop(RIGHT_MOTOR_P, true);
	}
	else
	{
		/* モータ出力 */
		ev3_motor_set_power(RIGHT_MOTOR_P, (int)pwm);
	}
}