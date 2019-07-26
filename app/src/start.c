#include "ev3api.h"
#include "start.h"
#include "tailcontrol.h"
#include "touchsensor.h"
#include "bluetooth.h"

Bluetooth bluetooth;

#define TAIL_MOTOR_P EV3_PORT_A /* テールモータポート */

#define START_CMD 1 /* リモートスタート用コマンド */

#define TAIL_ANGLE_STAND_UP 100 /* 完全停止時の角度[度] */
#define TAIL_ANGLE_START  (TAIL_ANGLE_STAND_UP + 2) /* スタート時の角度 */
#define START_DELAY_TIME  20 /* スタート遅延時間 */

/*
 * スタート初期化メソッド
 */
void Start_init() {
	Bluetooth_connect(&bluetooth); /* Bluetooth通信接続 */
	act_tsk(START_BLUETOOTH_TASK); /* Bluetooth受信メソッド開始 */
}

/*
 * 走行待機メソッド
 */
void Start_wait() {
	ev3_motor_reset_counts(TAIL_MOTOR_P); /* テールモータリセット */

	/* リモートスタート又はタッチセンサからスタート信号があるまで待機 */
	while (1) {

		TailControl_control(TAIL_ANGLE_STAND_UP); /* テールモータ制御 */

		if (bluetooth.bt_cmd == START_CMD) {
			break;
		}

		if (TouchSensor_is_pressed()) {
			break;
		}

		tslp_tsk(10);
	}

	ter_tsk(START_BLUETOOTH_TASK); /* Bluetooth信号受信タスク終了 */
	Bluetooth_disconnect(&bluetooth); /* Bluetooth通信終了 */
}

/*
 * 走行開始メソッド
 */
void Start_start() {
	int start_delay_counter = 0; /* スタート遅延カウンタ */

	/* スタート遅延 */
	while (1) {
		TailControl_control(TAIL_ANGLE_START); /* テールモータ制御 */

		start_delay_counter++;

		if (START_DELAY_TIME < start_delay_counter) {
			/* スタート遅延時間経過 */
			break;
		}

		tslp_tsk(10);
	}
}

/*
 * Bluetooth通信タスク
 */
void Start_bluetooth_task() {
	while (1) {
		Bluetooth_recv(&bluetooth);
	}
}