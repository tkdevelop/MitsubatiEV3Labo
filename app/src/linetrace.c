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
#include "direction.h"

PidControl pidControl;
Distance distance;
Direction direction;
Scene scene;
Clock clock;

/* モータポート */
#define LEFT_MOTOR_P EV3_PORT_C
#define RIGHT_MOTOR_P EV3_PORT_B
#define TAIL_MOTOR_P EV3_PORT_A

#define GYRO_OFFSET  0          /* ジャイロセンサオフセット値(角速度0[deg/sec]時) */
#define GYRO_OFFSET_LOOKUP (-20)		/* ルックアップゲート攻略用ジャイロセンサオフセット値 */

#define TAIL_ANGLE_DRIVE      3 /* バランス走行時の角度 */
#define TAIL_ANGLE_STAND_UP_1	  97//87  /* ルックアップ攻略-完全停止時の角度1 */
#define TAIL_ANGLE_STAND_UP_2	  87//75  /* ルックアップ攻略-完全停止時の角度2 */
#define TAIL_ANGLE_STAND_UP_3     95 /* ガレージ攻略-完全停止時の角度3 */
#define TAIL_ANGLE_STAND_UP_4     92 /* ガレージ攻略-完全停止時の角度4 */

void Linetrace_init(Linetrace* self, int threshold, int lookup_threshold) {
	self->forward = 0; /* 前進値初期化 */
	self->threshold = threshold; /* 閾値格納 */
	self->lookup_threshold = lookup_threshold; /* ルックアップゲート攻略用閾値 */

	/* 走行モータエンコーダリセット */
	WheelMotor_reset(LEFT_MOTOR_P);
	WheelMotor_reset(RIGHT_MOTOR_P);

	GyroSensor_reset(); /* ジャイロセンサリセット */

	BalanceControl_balance_init(); /* 倒立振子API初期化 */

	PidControl_init(&pidControl, self->threshold); /* Pid制御初期化 */

	Distance_init(&distance); /* 距離計初期化 */

	Direction_init(&direction); /* 方位計初期化 */

	Scene_init(&scene); /* 区間初期化 */
}

void Linetrace_run(Linetrace* self) {
	int turn = 0; /* 旋回命令 */
	signed char pwm_L, pwm_R; /* 左右モータPWM出力値 */
	int32_t motor_ang_l, motor_ang_r; /* 左右モータエンコーダ値 */
	int rate, /* ジャイロセンサ値 */
		volt;  /* バッテリ電圧 */

	float distance_num = 0.0; /* 走行距離 */
	int16_t ultrasonic_distance_num = 0; /* ルックアップゲートまでの距離 */

	int scene_num = -1; /* 走行区間 */

	/* 4msec周期で走行 */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON)) /* バックボタンで走行強制終了 */
		{
			break;
		}

		TailControl_control(TAIL_ANGLE_DRIVE); /* テール制御 */

		distance_num = Distance_calc(&distance); /* 走行距離計算 */

		scene_num = Scene_get_scene(&scene, distance_num); /* 走行区間を取得 */

		ultrasonic_distance_num = Ultrasonic_get_distance(); /* ルックアップゲートまでの距離を取得 */
		if (8 > ultrasonic_distance_num) { /* ルックアップゲートの8cm手前に到達したらループを抜ける */
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
		if (ev3_button_is_pressed(BACK_BUTTON)) /* バックボタンで走行強制終了 */
		{
			break;
		}

		time = Clock_get_time(&clock); /* タイム取得 */
		if (time < 100) { /* この間テールを下す */
			TailControl_control(TAIL_ANGLE_STAND_UP_1); /* テール制御 */
		}
		else if (time < 200) { /* この間テールを下す */
			TailControl_control(TAIL_ANGLE_STAND_UP_2); /* テール制御 */
		}
		else if (time < 300) {
			break;
		}

		distance_num = Distance_calc(&distance); /* 走行距離計算 */

		scene_num = Scene_get_scene(&scene, distance_num); /* 走行区間を取得 */

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

		tslp_tsk(4);
	}
	ter_tsk(LINETRACE_TIMER_TASK); /* タイマータスク終了 */

	Clock_reset(&clock); /* タイマーリセット */
	act_tsk(LINETRACE_TIMER_TASK); /* タイマータスク開始 */

	uint8_t reflect = 0; /* 反射光値 */

	/* ルックアップゲートを車体が通り過ぎるまで前進する */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON)) /* バックボタンで走行強制終了 */
		{
			break;
		}

		TailControl_control(TAIL_ANGLE_STAND_UP_2); /* テール制御 */

		reflect = ColorSensor_get_reflect(); /* 反射光値を取得 */

		turn = 50;

		if (reflect > self->lookup_threshold) { /* 操作量をマイナスに設定 */
			turn = -turn;
		}

		time = Clock_get_time(&clock); /* タイム取得 */
		if (time > 2700) { /* 2.7秒後抜ける */
			break;
		}

		ev3_motor_steer(LEFT_MOTOR_P, RIGHT_MOTOR_P, 10, turn); /* 走行体を前進 */

		tslp_tsk(4);
	}
	ter_tsk(LINETRACE_TIMER_TASK); /* タイマータスク終了 */

	Linetrace_rotate(-150.0); /* -150度回転 */

	Clock_reset(&clock); /* タイマーリセット */
	act_tsk(LINETRACE_TIMER_TASK); /* タイマータスク開始 */
	/* ルックアップゲートを車体が通り過ぎるまで前進する */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON)) /* バックボタンで走行強制終了 */
		{
			break;
		}

		TailControl_control(TAIL_ANGLE_STAND_UP_2); /* テール制御 */

		reflect = ColorSensor_get_reflect(); /* 反射光値を取得 */

		turn = 50;

		if (reflect > self->lookup_threshold) { /* 操作量をマイナスに設定 */
			turn = -turn;
		}

		time = Clock_get_time(&clock); /* タイム取得 */
		if (time > 5000) { /* 5秒後抜ける */
			break;
		}

		ev3_motor_steer(LEFT_MOTOR_P, RIGHT_MOTOR_P, 10, turn); /* 走行体を前進 */

		tslp_tsk(4);
	}
	ter_tsk(LINETRACE_TIMER_TASK); /* タイマータスク終了 */

	Linetrace_rotate(-160.0); /* -160度回転 */

	Clock_reset(&clock); /* タイマーリセット */
	act_tsk(LINETRACE_TIMER_TASK); /* タイマータスク開始 */
	/* ルックアップゲートを車体が通り過ぎるまで前進する */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON)) /* バックボタンで走行強制終了 */
		{
			break;
		}

		TailControl_control(TAIL_ANGLE_STAND_UP_2); /* テール制御 */

		reflect = ColorSensor_get_reflect(); /* 反射光値を取得 */

		turn = 50;

		if (reflect > self->lookup_threshold) { /* 操作量をマイナスに設定 */
			turn = -turn;
		}

		time = Clock_get_time(&clock); /* タイム取得 */
		if (time > 7000) { /* 7秒後抜ける */
			break;
		}

		ev3_motor_steer(LEFT_MOTOR_P, RIGHT_MOTOR_P, 10, turn); /* 走行体を前進 */

		tslp_tsk(4);
	}
	ter_tsk(LINETRACE_TIMER_TASK); /* タイマータスク終了 */
}

void Linetrace_rotate(float angle) {
	ev3_speaker_play_tone(NOTE_A4, 300);

	float distance_4ms_left = 0.0; /* 左タイヤの4ms間の走行距離 */
	float distance_4ms_right = 0.0; /* 右タイヤの4ms間の走行距離 */
	float direction_num = 0.0; /* 方位 */
	/* 回転する */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON)) /* バックボタンで走行強制終了 */
		{
			break;
		}

		TailControl_control(TAIL_ANGLE_STAND_UP_2); /* テール制御 */

		Distance_calc(&distance); /* 走行距離計算 */
		distance_4ms_left = Distance_get_distance_4ms_left(&distance);
		distance_4ms_right = Distance_get_distance_4ms_right(&distance);

		direction_num = Direction_calc(&direction, distance_4ms_left, distance_4ms_right); /* 方位を取得 */
		char m[20];
		sprintf(m, "dire : %4lf", direction_num);
		ev3_lcd_draw_string(m, 0, 90);
		if (direction_num < angle) {
			break;
		}

		/* 車体を回転 */
		ev3_motor_set_power(LEFT_MOTOR_P, -5);
		ev3_motor_set_power(RIGHT_MOTOR_P, 5);

		tslp_tsk(4);
	}

	Direction_reset(&direction); /* 方位をリセット */
}

void Linetrace_garage(Linetrace* self) {
	colorid_t color = 0;

	Clock_reset(&clock); /* タイマーリセット */
	act_tsk(LINETRACE_TIMER_TASK); /* タイマータスク開始 */
	int time = 0; /* タイム */
	/* 左右モータを一時停止することで次のフェーズでテールを下げることができる 
	 * 走りながらでは後ろに重心がかかるため、テールを下す力足りなくなる
	 */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON)) /* バックボタンで走行強制終了 */
		{
			break;
		}

		TailControl_control(TAIL_ANGLE_STAND_UP_2); /* テール制御 */

		ev3_motor_stop(LEFT_MOTOR_P, false);
		ev3_motor_stop(RIGHT_MOTOR_P, false);

		time = Clock_get_time(&clock); /* タイムを取得 */
		if (time > 500) { /* 0.5秒後ループを抜ける */
			break;
		}

		tslp_tsk(4);
	}
	ter_tsk(LINETRACE_TIMER_TASK); /* タイマータスク終了 */

	/* 青のラインを探す */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON)) /* バックボタンで走行強制終了 */
		{
			break;
		}

		TailControl_control(TAIL_ANGLE_STAND_UP_3); /* テール制御 */

		color = ColorSensor_get_color(); /* カラー取得 */
		if (color == 0) {
			ev3_motor_steer(LEFT_MOTOR_P, RIGHT_MOTOR_P, 10, -50);
		}
		else if (color == 1) {
			ev3_motor_steer(LEFT_MOTOR_P, RIGHT_MOTOR_P, 10, 50);
		}
		else if (color == 2) { /* 青のラインに到達したらループを抜ける */
			break;
		}

		tslp_tsk(4);
	}

	ter_tsk(LINETRACE_TIMER_TASK); /* タイマータスク終了 */
	ev3_speaker_play_tone(NOTE_A4, 300);

	Clock_reset(&clock); /* タイマーリセット */
	act_tsk(LINETRACE_TIMER_TASK); /* タイマータスク開始 */
	/* 次のフェーズのバックで倒れないように遅延を挟む */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON)) /* バックボタンで走行強制終了 */
		{
			break;
		}

		TailControl_control(TAIL_ANGLE_STAND_UP_3); /* テール制御 */

		time = Clock_get_time(&clock); /* タイム取得 */
		if (time > 500) {
			break;
		}

		ev3_motor_stop(LEFT_MOTOR_P, false);
		ev3_motor_stop(RIGHT_MOTOR_P, false);

		tslp_tsk(4);
	}
	ter_tsk(LINETRACE_TIMER_TASK); /* タイマータスク終了 */

	/* 青のラインから出る */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON)) /* バックボタンで走行強制終了 */
		{
			break;
		}

		TailControl_control(TAIL_ANGLE_STAND_UP_3 - 5); /* テール制御 */

		color = ColorSensor_get_color(); /* カラー取得 */
		if (color == 0) {
			ev3_motor_steer(LEFT_MOTOR_P, RIGHT_MOTOR_P, -10, 50);
		}
		else if (color == 2) {
			ev3_motor_steer(LEFT_MOTOR_P, RIGHT_MOTOR_P, -10, -50);
		}
		else if (color == 1) { /* 黒のラインに到達したらループを抜ける */
			break;
		}

		tslp_tsk(4);
	}
	ev3_speaker_play_tone(NOTE_F4, 300);

	Clock_reset(&clock); /* タイマーリセット */
	act_tsk(LINETRACE_TIMER_TASK); /* タイマータスク開始 */
	time = 0; /* タイム */
	/* 次のフェーズの前進で倒れないように遅延を挟む */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON)) /* バックボタンで走行強制終了 */
		{
			break;
		}

		TailControl_control(TAIL_ANGLE_STAND_UP_3); /* テール制御 */

		time = Clock_get_time(&clock); /* タイム取得 */
		if (time > 500) {
			break;
		}

		ev3_motor_stop(LEFT_MOTOR_P, false);
		ev3_motor_stop(RIGHT_MOTOR_P, false);

		tslp_tsk(4);
	}
	ter_tsk(LINETRACE_TIMER_TASK); /* タイマータスク終了 */

	int turn = 0;

	int reflect = 0; /* 反射光値 */

	int start_distance = Distance_calc(&distance); /* ガレージ停車スタート位置走行距離 */
	int now_distance = 0; /* 現在の走行距離 */
	/* ガレージ停車位置まで前進 */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON)) /* バックボタンで走行強制終了 */
		{
			break;
		}

		TailControl_control(TAIL_ANGLE_STAND_UP_4); /* テール制御 */

		now_distance = Distance_calc(&distance); /* 走行距離取得 */

		if ((now_distance - start_distance) > 270) { /* 27cm前進したらループを抜ける */
			break;
		}

		reflect = ColorSensor_get_reflect(); /* 反射光値を取得 */

		turn = 50;

		if (reflect > self->lookup_threshold) { /* 操作量をマイナスに設定 */
			turn = -50;
		}

		ev3_motor_steer(LEFT_MOTOR_P, RIGHT_MOTOR_P, 10, turn); /* 走行体を前進 */

		tslp_tsk(4);
	}

	ev3_speaker_play_tone(NOTE_B4, 300);

	/* 停車 */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON)) /* バックボタンで走行強制終了 */
		{
			break;
		}

		TailControl_control(TAIL_ANGLE_STAND_UP_4); /* テール制御 */

		ev3_motor_stop(LEFT_MOTOR_P, false);
		ev3_motor_stop(RIGHT_MOTOR_P, false);

		tslp_tsk(4);
	}
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
