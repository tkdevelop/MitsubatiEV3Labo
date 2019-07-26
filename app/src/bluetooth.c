#include "ev3api.h"
#include "bluetooth.h"

/*
 * Bluetooth�ʐM�ڑ����\�b�h
 *
 * @param self �����̃|�C���^
 */
void Bluetooth_connect(Bluetooth* self) {
	self->bt_file = ev3_serial_open_file(EV3_SERIAL_BT); /* Bluetooth�ʐM�p�t�@�C���I�[�v�� */
	assert(self->bt_file != NULL);

	self->bt_cmd = 0; /* �M�������� */
}

/*
 * Bluetooth�ʐM�I�����\�b�h
 *
 * @param self �����̃|�C���^
 */
void Bluetooth_disconnect(Bluetooth* self) {
	fclose(self->bt_file);
}

/*
 * Bluetooth�M����M���\�b�h
 *
 * @param self �����̃|�C���^
 */
void Bluetooth_recv(Bluetooth* self) {
	char c = fgetc(self->bt_file); /* �M����M */
	fputc(c, self->bt_file); /* �G�R�[�o�b�N */
	if (c == '1') {
		self->bt_cmd = 1;
	}
}