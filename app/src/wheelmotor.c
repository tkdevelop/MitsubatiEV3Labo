#include "ev3api.h"
#include "wheelmotor.h"

/*
 * モータリセットメソッド
 */
void WheelMotor_reset(int motor_port) {
	ev3_motor_reset_counts(motor_port);
}

/*
 * モータ回転角度取得メソッド
 *
 * return angle 回転角度
 */
int32_t WheelMotor_get_angle(int motor_port) {
	int32_t angle = ev3_motor_get_counts(motor_port);
	return angle;
}

/*
 * モータ出力制御
 */
void WheelMotor_set_tire_motor(int motor_port,int8_t pwm) {
	if (0x00 == pwm)
	{
		/* PWMが0である場合、モータ停止 */
		ev3_motor_stop(motor_port, true);
	}
	else
	{
		/* モータ出力 */
		ev3_motor_set_power(motor_port, (int)pwm);
	}
}