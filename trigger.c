#include "ev3api.h"
#include "trigger.h"
#include "touchsensor.h"

TouchSensor touchSensor;

#define START_CMD 1 /* リモートスタート用コマンド */

static FILE* bt_file; /* シリアルポートのファイル */
static int bt_cmd; /* 受信したコマンド */

/*
 * トリガー初期化メソッド
 *
 * @param self 自分のポインタ
 */
void Trigger_init(Trigger* self) {
	
}

/*
 * 走行待機メソッド
 *
 * @param self 自分のポインタ
 */
void Trigger_wait(Trigger* self) {
	Trigger_bt_connect(); /* Bluetooth通信接続 */
	act_tsk(TRIGGER_BT_RECV_TASK); /* Bluetooth受信メソッド開始 */

	/* リモートスタート又はタッチセンサーからスタート信号があるまで待機 */
	while (1) {

		//TODO:Tail-control

		if (bt_cmd == START_CMD) {
			break;
		}

		TouchSensor_check_input(&touchSensor);
		if (touchSensor.input == START_CMD) {
			break;
		}

		tslp_tsk(10);
	}

	ev3_lcd_draw_string("finished", 0, 110);
	Trigger_bt_close(); /* Bluetooth通信終了 */
}

/*
 * Bluetooth通信接続メソッド
 */
void Trigger_bt_connect() {
	bt_file = ev3_serial_open_file(EV3_SERIAL_BT);
	assert(bt_file != NULL);
}

/*
 * Bluetooth受信メソッド
 *
 * @param self 自分のポインタ
 */
void Trigger_bt_recv_task(intptr_t unused) {
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
void Trigger_bt_close() {
	fclose(bt_file); //接続終了
}