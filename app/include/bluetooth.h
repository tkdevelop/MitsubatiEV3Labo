#ifndef _BLUETOOTH_H_
#define _BLUETOOTH_H_

typedef struct {
	FILE* bt_file; /* Bluetooth�ʐM�p�t�@�C���|�C���^ */
	int bt_cmd; /* �M�� */
}Bluetooth;
void Bluetooth_connect(Bluetooth* self);
void Bluetooth_disconnect(Bluetooth* self);
void Bluetooth_recv(Bluetooth* self);

#endif