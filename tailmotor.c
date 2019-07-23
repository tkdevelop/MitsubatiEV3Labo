#include "ev3api.h"
#include "tailmotor.h"

#define TAIL_MOTOR_P EV3_PORT_A /* テールモーターポート */

#define P_GAIN             2.5F /* 完全停止用モーター制御比例係数 */
#define PWM_ABS_MAX          60 /* 完全停止用モーター制御PWM絶対最大値 */

/*
 * テール駆動メソッド
 */
void TailMotor_control(signed int angle) {
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