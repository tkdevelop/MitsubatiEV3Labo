#include "ev3api.h"
#include "tailcontrol.h"

#define TAIL_MOTOR_P EV3_PORT_A /* テールモータポート */

#define P_GAIN             2.5F /* 完全停止用モータ制御比例係数 */
#define PWM_ABS_MAX          60 /* 完全停止用モータ制御PWM絶対最大値 */

/*
 * テールモータリセットメソッド
 */
void TailControl_reset() {
	ev3_motor_reset_counts(TAIL_MOTOR_P);
}

/*
 * テール駆動メソッド
 */
void TailControl_control(signed int angle) {
	signed int pwm = (signed int)((angle - ev3_motor_get_counts(TAIL_MOTOR_P))*P_GAIN); /* 比例制御 */
	/* PWM出力飽和処理 */
	if (pwm > PWM_ABS_MAX)
	{
		pwm = PWM_ABS_MAX;
	}
	else if (pwm < -PWM_ABS_MAX)
	{
		pwm = -PWM_ABS_MAX;
	}

	if (pwm == 0)
	{
		ev3_motor_stop(TAIL_MOTOR_P, true);
	}
	else
	{
		ev3_motor_set_power(TAIL_MOTOR_P, (signed char)pwm);
	}
}