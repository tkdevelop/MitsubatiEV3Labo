#include "ev3api.h"
#include "linetrace.h"
#include "balancecontrol.h"
#include "tailcontrol.h"
#include "leftmotor.h"
#include "rightmotor.h"
#include "gyrosensor.h"
#include "pid.h"
#include "touchsensor.h"

Pid pid;

/* モータポート */
#define LEFT_MOTOR_P EV3_PORT_C
#define RIGHT_MOTOR_P EV3_PORT_B
#define TAIL_MOTOR_P EV3_PORT_A

#define GYRO_OFFSET  0          /* ジャイロセンサオフセット値(角速度0[deg/sec]時) */

#define TAIL_ANGLE_DRIVE      3 /* バランス走行時の角度 */
#define FORWARD 40 /* 前進値 */

void Linetrace_init(int threshold) {
	/* 走行モータエンコーダリセット */
	LeftMotor_reset();
	RightMotor_reset();

	GyroSensor_reset(); /* ジャイロセンサリセット */

	BalanceControl_balance_init(); /* 倒立振子API初期化 */

	Pid_init(&pid, threshold); /* Pid初期化 */
}

void Linetrace_run() {
	int forward = 70; /* 前進値 */
	int turn = 0; /* 旋回命令 */
	signed char pwm_L, pwm_R; /* 左右モータPWM出力値 */
	int32_t motor_ang_l, motor_ang_r; /* 左右モータエンコーダ値 */
	int rate, /* ジャイロセンサ値 */
		volt;  /* バッテリ電圧 */

	char m[20];
	FILE *logfile = fopen("/log.txt", "w");

	/* 4msec周期で走行 */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON) || TouchSensor_is_pressed()) /* バックボタンで走行強制終了 */
		{
			fclose(logfile);
			break;
		}

		TailControl_control(TAIL_ANGLE_DRIVE); /* テール制御 */

		turn = Pid_calc(&pid); /* PID取得 */
		sprintf(m, "pid :%3d", turn);
		ev3_lcd_draw_string(m, 0, 110);
		fprintf(logfile, "%d\r\n", turn);

		/* 倒立振子制御API に渡すパラメータを取得する */
		motor_ang_l = LeftMotor_get_angle();
		motor_ang_r = RightMotor_get_angle();
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
		LeftMotor_set_tire_motor(pwm_L);
		RightMotor_set_tire_motor(pwm_R);

		tslp_tsk(4);
	}
}