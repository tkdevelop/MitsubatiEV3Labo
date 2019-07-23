#include "ev3api.h"
#include "bluetooth.h"

void Bluetooth_connect(Bluetooth* self) {
	self->bt_file = ev3_serial_open_file(EV3_SERIAL_BT); /* 接続 */
	assert(self->bt_file != NULL);
}

void Bluetooth_recv(Bluetooth* self) {
	int c = fgetc(self->bt_file); /* コマンド受信 */

	switch (c) {
	case '1':
		self->bt_cmd = 1;
		break;
	default:
		break;
	}

	fputc(c, self->bt_file); /* エコーバック */
}