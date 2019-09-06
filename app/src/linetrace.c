#include "ev3api.h"
#include "linetrace.h"
#include "balancecontrol.h"
#include "tailcontrol.h"
#include "wheelmotor.h"
#include "gyrosensor.h"
#include "pidcontrol.h"
#include "touchsensor.h"
#include "distance.h"
#include "scene.h"
#include "runningstyle.h"
#include "ultrasonic.h"
#include "clock.h"
#include "colorsensor.h"

PidControl pidControl;
Distance distance;
Scene scene;
Clock clock;

/* モータポート */
#define LEFT_MOTOR_P EV3_PORT_C
#define RIGHT_MOTOR_P EV3_PORT_B
#define TAIL_MOTOR_P EV3_PORT_A

#define GYRO_OFFSET  0          /* ジャイロセンサオフセット値(角速度0[deg/sec]時) */
#define GYRO_OFFSET_LOOKUP (-20)		/* ルックアップゲート攻略用ジャイロセンサオフセット値 */

#define TAIL_ANGLE_DRIVE      3 /* バランス走行時の角度 */
#define TAIL_ANGLE_STAND_UP_1	  87 /* ルックアップ攻略-完全停止時の角度1 */
#define TAIL_ANGLE_STAND_UP_2	  75 /* ルックアップ攻略-完全停止時の角度2 */
#define FORWARD 40 /* 前進値 */

void Linetrace_init(Linetrace* self, int threshold) {
	self->forward = 0; /* 前進値初期化 */
	self->threshold = threshold; /* 閾値格納 */

	/* 走行モータエンコーダリセット */
	WheelMotor_reset(LEFT_MOTOR_P);
	WheelMotor_reset(RIGHT_MOTOR_P);

	GyroSensor_reset(); /* ジャイロセンサリセット */

	BalanceControl_balance_init(); /* 倒立振子API初期化 */

	PidControl_init(&pidControl, self->threshold); /* Pid制御初期化 */

	Distance_init(&distance); /* 自己位置推定初期化 */

	Scene_init(&scene); /* 区間初期化 */
}

void Linetrace_run(Linetrace* self) {
	int turn = 0; /* 旋回命令 */
	signed char pwm_L, pwm_R; /* 左右モータPWM出力値 */
	int32_t motor_ang_l, motor_ang_r; /* 左右モータエンコーダ値 */
	int rate, /* ジャイロセンサ値 */
		volt;  /* バッテリ電圧 */

	float distance_num = 0.0; /* 走行距離 */

	int scene_num = -1; /* 走行区間 */
	char m[21];

	/* 4msec周期で走行 */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON) || TouchSensor_is_pressed()) /* バックボタンで走行強制終了 */
		{
			break;
		}

		TailControl_control(TAIL_ANGLE_DRIVE); /* テール制御 */

		distance_num = Distance_calc(&distance); /* 走行距離計算 */

		scene_num = Scene_get_scene(&scene, distance_num); /* 走行区間を取得 */

		sprintf(m, "gate : %4d", Ultrasonic_get_distance());
		ev3_lcd_draw_string(m, 0, 110);
		if (8 > Ultrasonic_get_distance()) { /* ルックアップゲートの5cm手前に到達したらループを抜ける */
			break;
		}

		RunningStyle_switch(scene_num, self, &pidControl); /* 走法切り替え */

		turn = PidControl_calc(&pidControl); /* 操作量取得 */

		/* 倒立振子制御API に渡すパラメータを取得する */
		motor_ang_l = WheelMotor_get_angle(LEFT_MOTOR_P);
		motor_ang_r = WheelMotor_get_angle(RIGHT_MOTOR_P);
		rate = GyroSensor_get_rate();
		volt = ev3_battery_voltage_mV();

		BalanceControl_backlash_cancel(pwm_L, pwm_R, &motor_ang_l, &motor_ang_r); /* バックラッシュキャンセル */

		/* 倒立振子制御APIを呼び出し、倒立走行するための */
		/* 左右モータ出力値を得る */
		BalanceControl_balance_control(
			(float)self->forward,
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

void Linetrace_lookup(Linetrace* self) {
	int turn = 0; /* 旋回命令 */
	signed char pwm_L, pwm_R; /* 左右モータPWM出力値 */
	int32_t motor_ang_l, motor_ang_r; /* 左右モータエンコーダ値 */
	int rate, /* ジャイロセンサ値 */
		volt;  /* バッテリ電圧 */

	float distance_num = 0.0; /* 走行距離 */

	int time = 0; /* タイム */
	act_tsk(LINETRACE_TIMER_TASK); /* タイマータスク開始 */

	int scene_num = -1; /* 走行区間 */
	/* テールを下ろす */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON) || TouchSensor_is_pressed()) /* バックボタンで走行強制終了 */
		{
			break;
		}

		TailControl_control(TAIL_ANGLE_STAND_UP_1); /* テール制御 */

		distance_num = Distance_calc(&distance); /* 走行距離計算 */

		scene_num = Scene_get_scene(&scene, distance_num); /* 走行区間を取得 */

		time = Clock_get_time(&clock); /* タイム取得 */
		if (time > 200) { /* この間テールを下す */
			break;
		}
		else {

			RunningStyle_switch(scene_num, self, &pidControl); /* 走法切り替え */

			turn = PidControl_calc(&pidControl); /* 操作量取得 */

			/* 倒立振子制御API に渡すパラメータを取得する */
			motor_ang_l = WheelMotor_get_angle(LEFT_MOTOR_P);
			motor_ang_r = WheelMotor_get_angle(RIGHT_MOTOR_P);
			rate = GyroSensor_get_rate();
			volt = ev3_battery_voltage_mV();

			BalanceControl_backlash_cancel(pwm_L, pwm_R, &motor_ang_l, &motor_ang_r); /* バックラッシュキャンセル */

			/* 倒立振子制御APIを呼び出し、倒立走行するための */
			/* 左右モータ出力値を得る */
			BalanceControl_balance_control(
				(float)self->forward,
				(float)turn,
				(float)rate,
				(float)GYRO_OFFSET_LOOKUP,
				(float)motor_ang_l,
				(float)motor_ang_r,
				(float)volt,
				(signed char*)&pwm_L,
				(signed char*)&pwm_R);

			/* モータ停止時のブレーキ設定 */
			WheelMotor_set_tire_motor(LEFT_MOTOR_P, pwm_L);
			WheelMotor_set_tire_motor(RIGHT_MOTOR_P, pwm_R);
		}

		tslp_tsk(4);
	}
	ter_tsk(LINETRACE_TIMER_TASK); /* タイマータスク終了 */

	Clock_reset(&clock); /* タイマーリセット */
	act_tsk(LINETRACE_TIMER_TASK); /* タイマータスク開始 */

	uint8_t reflect = 0; /* 反射光値 */

	/* ルックアップゲートを車体が通り過ぎるまで前進・後進をする */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON) || TouchSensor_is_pressed()) /* バックボタンで走行強制終了 */
		{
			break;
		}

		TailControl_control(TAIL_ANGLE_STAND_UP_2); /* テール制御 */

		turn = 50;

		reflect = ColorSensor_get_reflect(); /* 反射光値を取得 */
		reflect += 15; /* カラーセンサーが傾く分補正 */

		if (reflect > self->threshold) { /* 操作量をマイナスに設定 */
			turn = -turn;
		}

		time = Clock_get_time(&clock); /* タイム取得 */
		if (time < 2900) {
			ev3_motor_steer(LEFT_MOTOR_P, RIGHT_MOTOR_P, 10, turn); /* 走行体を前進 */
		}
		else if (time < 3600) {
			ev3_motor_steer(LEFT_MOTOR_P, RIGHT_MOTOR_P, 10, 180); /* 走行体を180度回転 */
		}
		else if (time < 7900) {
			ev3_motor_steer(LEFT_MOTOR_P, RIGHT_MOTOR_P, 10, turn); /* 走行体を前進 */
		}
		else if (time < 8800) {
			ev3_motor_steer(LEFT_MOTOR_P, RIGHT_MOTOR_P, 10, 180); /* 走行体を180度回転 */
		}
		else if (time < 14000) {
			ev3_motor_steer(LEFT_MOTOR_P, RIGHT_MOTOR_P, 10, turn); /* 走行体を前進 */
		}
		else {
			break;
		}

		tslp_tsk(4);
	}
	ter_tsk(LINETRACE_TIMER_TASK); /* タイマータスク終了 */
}

void Linetrace_garage(Linetrace* self) {
	/*while (1) {

	}*/
}

/*
 * タイマータスク
 */
void Linetrace_timer_task() {
	while (1) {
		Clock_time_countup(&clock);
		tslp_tsk(1);
	}
}