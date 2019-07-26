#include "ev3api.h"
#include "linetrace.h"
#include "balancecontrol.h"
#include "tailcontrol.h"
#include "wheelmotor.h"
#include "gyrosensor.h"
#include "pidcontrol.h"
#include "touchsensor.h"
#include "distance.h"
#include "direction.h"

PidControl pidControl;
Distance distance;
Direction direction;

/* モータポート */
#define LEFT_MOTOR_P EV3_PORT_C
#define RIGHT_MOTOR_P EV3_PORT_B
#define TAIL_MOTOR_P EV3_PORT_A

#define GYRO_OFFSET  0          /* ジャイロセンサオフセット値(角速度0[deg/sec]時) */

#define TAIL_ANGLE_DRIVE      3 /* バランス走行時の角度 */
#define FORWARD 40 /* 前進値 */

void Linetrace_init(int threshold) {
	/* 走行モータエンコーダリセット */
	WheelMotor_reset(LEFT_MOTOR_P);
	WheelMotor_reset(RIGHT_MOTOR_P);

	GyroSensor_reset(); /* ジャイロセンサリセット */

	BalanceControl_balance_init(); /* 倒立振子API初期化 */

	PidControl_init(&pidControl, threshold); /* Pid制御初期化 */

	Distance_init(&distance); /* 距離計初期化 */
	Direction_init(&direction,&distance); /* 方位計初期化 */
}

void Linetrace_run() {
	int forward = 60; /* 前進値 */
	int turn = 0; /* 旋回命令 */
	signed char pwm_L, pwm_R; /* 左右モータPWM出力値 */
	int32_t motor_ang_l, motor_ang_r; /* 左右モータエンコーダ値 */
	int rate, /* ジャイロセンサ値 */
		volt;  /* バッテリ電圧 */

	float distance_num = 0.0; /* 走行距離 */
	float direction_num = 0.0; /* 方位 */

	FILE *logfile = fopen("/log.txt", "w");

	/* 4msec周期で走行 */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON) || TouchSensor_is_pressed()) /* バックボタンで走行強制終了 */
		{
			fclose(logfile);
			break;
		}

		TailControl_control(TAIL_ANGLE_DRIVE); /* テール制御 */

		Distance_update(&distance); /* 距離計を更新 */
		Direction_update(&direction); /* 方位計を更新 */

		distance_num = Distance_get_distance(&distance); /* 走行距離取得 */
		direction_num = Direction_get_direction(&direction); /* 方位取得 */
		fprintf(logfile, "%lf : %lf\r\n", distance_num,direction_num);

		turn = PidControl_calc(&pidControl); /* PID取得 */

		/* 倒立振子制御API に渡すパラメータを取得する */
		motor_ang_l = WheelMotor_get_angle(LEFT_MOTOR_P);
		motor_ang_r = WheelMotor_get_angle(RIGHT_MOTOR_P);
		rate = GyroSensor_get_rate();
		volt = ev3_battery_voltage_mV();

		BalanceControl_backlash_cancel(pwm_L, pwm_R, &motor_ang_l, &motor_ang_r); /* バックラッシュキャンセル */

		/* 倒立振子制御APIを呼び出し、倒立走行するための */
		/* 左右モータ出力値を得る */
		BalanceControl_balance_control(
			(float)forward,
			(float)turn,
			(float)rate,
			(float)GYRO_OFFSET,
			(float)motor_ang_l,
			(float)motor_ang_r,
			(float)volt,
			(signed char*)&pwm_L,
			(signed char*)&pwm_R);

		/* モータ停止時のブレーキ設定 */
		WheelMotor_set_tire_motor(LEFT_MOTOR_P, pwm_L);
		WheelMotor_set_tire_motor(RIGHT_MOTOR_P, pwm_R);

		tslp_tsk(4);
	}
}