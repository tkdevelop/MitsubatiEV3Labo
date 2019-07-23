#include "ev3api.h"
#include "linetrace.h"
#include "balancer.h"
#include "tailcontrol.h"

/* モーターポート */
#define LEFT_MOTOR_P EV3_PORT_C
#define RIGHT_MOTOR_P EV3_PORT_B
#define TAIL_MOTOR_P EV3_PORT_A

#define GYRO_SENSOR_P EV3_PORT_4 /* ジャイロセンサ―ポート */
#define GYRO_OFFSET  0          /* ジャイロセンサオフセット値(角速度0[deg/sec]時) */

#define TAIL_ANGLE_DRIVE      3 /* バランス走行時の角度 */
#define FORWARD 40 /* 前進値 */

void Linetrace_init() {
	/* 走行モーターエンコーダ―リセット */
	ev3_motor_reset_counts(LEFT_MOTOR_P);
	ev3_motor_reset_counts(RIGHT_MOTOR_P);

	ev3_gyro_sensor_reset(GYRO_SENSOR_P); /* ジャイロセンサ―リセット */

	balance_init(); /* 倒立振子API初期化 */
}

void Linetrace_run() {
	//TODO:pid
	int forward = 10;
	int turn = 0;
	signed char pwm_L, pwm_R; /* 左右モーターPWM出力 */

	int32_t motor_ang_l, motor_ang_r;
	int gyro, volt;

	/* 4msec周期で走行 */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON)) /* バックボタンで走行強制終了 */
		{
			break;
		}

		TailControl_control(TAIL_ANGLE_DRIVE);

		/* 倒立振子制御API に渡すパラメーターを取得する */
		motor_ang_l = ev3_motor_get_counts(LEFT_MOTOR_P);
		motor_ang_r = ev3_motor_get_counts(RIGHT_MOTOR_P);
		gyro = ev3_gyro_sensor_get_rate(GYRO_SENSOR_P);
		volt = ev3_battery_voltage_mV();

		backlash_cancel(pwm_L, pwm_R, &motor_ang_l, &motor_ang_r); /* バックラッシュキャンセル */

		/* 倒立振子制御APIを呼び出し、倒立走行するための */
		/* 左右モーター出力値を得る */
		balance_control(
			(float)forward,
			(float)turn,
			(float)gyro,
			(float)GYRO_OFFSET,
			(float)motor_ang_l,
			(float)motor_ang_r,
			(float)volt,
			(signed char*)&pwm_L,
			(signed char*)&pwm_R);

		set_tire_motor(LEFT_MOTOR_P, pwm_L); /* モーター停止時のブレーキ設定 */
		set_tire_motor(RIGHT_MOTOR_P, pwm_R);
		
		tslp_tsk(4);
	}
}

void backlash_cancel(signed char lpwm, signed char rpwm, int32_t *lenc, int32_t *renc)
{
	const int BACKLASHHALF = 4;   // バックラッシュの半分[deg]

	if (lpwm < 0) *lenc += BACKLASHHALF;
	else if (lpwm > 0) *lenc -= BACKLASHHALF;

	if (rpwm < 0) *renc += BACKLASHHALF;
	else if (rpwm > 0) *renc -= BACKLASHHALF;
}

/* タイヤモータ出力制御 */
void set_tire_motor(motor_port_t port, int8_t pwm)
{
	if (0x00 == pwm)
	{
		/* PWMが0である場合、モータ停止 */
		ev3_motor_stop(port, true);
	}
	else
	{
		/* モータ出力 */
		ev3_motor_set_power(port, (int)pwm);
	}
}