#include "ev3api.h"
#include "start.h"
#include "tailcontrol.h"

#define TAIL_MOTOR_P EV3_PORT_A /* テールモーターポート */
#define TOUCH_SENSOR_P EV3_PORT_1 /* タッチセンサーポート */

#define START_CMD 1 /* リモートスタート用コマンド */
static FILE* bt_file = NULL; /* シリアルポートのファイル */
static int bt_cmd = 0; /* 受信したコマンド */

#define TAIL_ANGLE_STAND_UP 95 /* 完全停止時の角度[度] */
#define TAIL_ANGLE_START  (TAIL_ANGLE_STAND_UP + 3) /* スタート時の角度 */
#define START_DELAY_TIME  (15) /* スタート遅延時間 */

/*
 * スタート初期化メソッド
 */
void Start_init() {
	Start_bt_connect(); /* Bluetooth通信接続 */
	act_tsk(START_BT_RECV_TASK); /* Bluetooth受信メソッド開始 */
}

/*
 * 走行待機メソッド
 */
void Start_wait() {
	ev3_motor_reset_counts(TAIL_MOTOR_P); /* テールモーターリセット */

	/* リモートスタート又はタッチセンサーからスタート信号があるまで待機 */
	while (1) {

		TailControl_control(TAIL_ANGLE_STAND_UP); /* テールモーター制御 */

		if (bt_cmd == START_CMD) {
			break;
		}

		if (ev3_touch_sensor_is_pressed(TOUCH_SENSOR_P)) {
			break;
		}

		tslp_tsk(10);
	}

	ter_tsk(START_BT_RECV_TASK); /* Bluetooth信号受信タスク終了 */
	Start_bt_close(); /* Bluetooth通信終了 */
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
 * Bluetooth通信接続メソッド
 */
void Start_bt_connect() {
	bt_file = ev3_serial_open_file(EV3_SERIAL_BT);
	assert(bt_file != NULL);
}

/*
 * Bluetooth信号受信タスク
 *
 * @param self 自分のポインタ
 */
void Start_bt_recv_task(intptr_t unused) {
	while (1)
	{
		uint8_t c = fgetc(bt_file); /* 受信 */
		switch (c)
		{
		case '1':
			bt_cmd = 1;
			break;
		default:
			break;
		}
		fputc(c, bt_file); /* エコーバック */
	}
}

/*
 * Bluetooth通信終了メソッド
 */
void Start_bt_close() {
	fclose(bt_file); //接続終了
}