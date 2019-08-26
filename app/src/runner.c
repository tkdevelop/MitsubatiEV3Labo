#include "ev3api.h"
#include "runner.h"
#include "calibration.h"
#include "start.h"
#include "linetrace.h"
#include "battery.h"

Calibration calibration;
Linetrace linetrace;

/* モータポート */
#define LEFT_MOTOR_P EV3_PORT_C
#define RIGHT_MOTOR_P EV3_PORT_B
#define TAIL_MOTOR_P EV3_PORT_A

/* センサポート */
#define COLOR_SENSOR_P EV3_PORT_3
#define TOUCH_SENSOR_P EV3_PORT_1
#define GYRO_SENSOR_P EV3_PORT_4

/*
 * 走行体初期化メソッド
 *
 * @param self 自分のポインタ
 */
void Runner_init() {
	/* モータポート設定 */
	ev3_motor_config(LEFT_MOTOR_P, LARGE_MOTOR);
	ev3_motor_config(RIGHT_MOTOR_P, LARGE_MOTOR);
	ev3_motor_config(TAIL_MOTOR_P, LARGE_MOTOR);

	/* センサポート設定 */
	ev3_sensor_config(COLOR_SENSOR_P, COLOR_SENSOR);
	ev3_sensor_config(TOUCH_SENSOR_P, TOUCH_SENSOR);
	ev3_sensor_config(GYRO_SENSOR_P, GYRO_SENSOR);

	/* LCD画面初期化 */
	ev3_lcd_set_font(EV3_FONT_MEDIUM); /* ミディアムフォント */

	act_tsk(RUNNER_BATTERY_TASK); /* バッテリ残量表示タスク開始 */
}

/*
 * 走行プログラム開始メソッド
 *
 * @param self 自分のポインタ
 */
void Runner_start() {
	/* キャリブレーション開始 */
	Calibration_init(&calibration);
	Calibration_start(&calibration);

	/* 走行開始 */
	Start_init();
	Start_wait();
	Start_start();

	/* 走行 */
	Linetrace_init(&linetrace,calibration.threshold);
	Linetrace_run(&linetrace);

	/* モータ出力停止 */
	ev3_motor_stop(LEFT_MOTOR_P, false);
	ev3_motor_stop(RIGHT_MOTOR_P, false);
	ev3_motor_stop(TAIL_MOTOR_P, false);

	ter_tsk(RUNNER_BATTERY_TASK); /* バッテリ残量表示タスク終了 */
}

/*
 * バッテリ残量表示タスク
 */
void Runner_battery_task() {
	while (1) {
		Battery_display(); /* バッテリ残量表示 */
	}
}