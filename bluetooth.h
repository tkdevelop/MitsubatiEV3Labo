#ifndef _BLUETOOTH_H_
#define _BLUETOOTH_H_

typedef struct {
	FILE* bt_file; /* �V���A���|�[�g�̃t�@�C�� */
	int bt_cmd; /* ��M�����R�}���h */
}Bluetooth;
void Bluetooth_connect(Bluetooth* self);
void Bluetooth_recv(Bluetooth* self);

#endif