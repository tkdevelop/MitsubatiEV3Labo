#ifndef _BLUETOOTH_H_
#define _BLUETOOTH_H_

typedef struct {
	FILE* bt_file; /* シリアルポートのファイル */
	int bt_cmd; /* 受信したコマンド */
}Bluetooth;
void Bluetooth_connect(Bluetooth* self);
void Bluetooth_recv(Bluetooth* self);

#endif