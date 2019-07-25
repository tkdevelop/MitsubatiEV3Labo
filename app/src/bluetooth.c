#include "ev3api.h"
#include "bluetooth.h"

/*
 * Bluetooth通信接続メソッド
 *
 * @param self 自分のポインタ
 */
void Bluetooth_connect(Bluetooth* self) {
	self->bt_file = ev3_serial_open_file(EV3_SERIAL_BT);
	assert(self->bt_file != NULL);
}

/*
 * Bluetooth通信終了メソッド
 *
 * @param self 自分のポインタ
 */
void Bluetooth_disconnect(Bluetooth* self) {
	fclose(self->bt_file);
}

/*
 * Bluetooth信号受信メソッド
 *
 * @param self 自分のポインタ
 */
void Bluetooth_recv(Bluetooth* self) {
	char c = fgetc(self->bt_file); /* 信号受信 */
	fputc(c, self->bt_file); /* エコーバック */
	if (c == '1') {
		self->bt_cmd = 1;
	}
}