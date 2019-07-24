#include "ev3api.h"
#include "linetrace.h"
#include "balancer.h"
#include "tailcontrol.h"
#include "leftmotor.h"
#include "rightmotor.h"
#include "gyrosensor.h"

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
	LeftMotor_reset();
	RightMotor_reset();

	GyroSensor_reset(); /* ジャイロセンサ―リセット */

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
		motor_ang_l = LeftMotor_get_angle();
		motor_ang_r = RightMotor_get_angle();
		gyro = GyroSensor_get_rate();
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

		/* モーター停止時のブレーキ設定 */
		LeftMotor_set_tire_motor(pwm_L);
		RightMotor_set_tire_motor(pwm_R);
		
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