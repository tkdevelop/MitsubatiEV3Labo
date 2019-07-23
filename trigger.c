#include "ev3api.h"
#include "trigger.h"
#include "touchsensor.h"

TouchSensor touchSensor;

#define START_CMD 1 /* �����[�g�X�^�[�g�p�R�}���h */

static FILE* bt_file; /* �V���A���|�[�g�̃t�@�C�� */
static int bt_cmd; /* ��M�����R�}���h */

/*
 * �g���K�[���������\�b�h
 *
 * @param self �����̃|�C���^
 */
void Trigger_init(Trigger* self) {
	
}

/*
 * ���s�ҋ@���\�b�h
 *
 * @param self �����̃|�C���^
 */
void Trigger_wait(Trigger* self) {
	Trigger_bt_connect(); /* Bluetooth�ʐM�ڑ� */
	act_tsk(TRIGGER_BT_RECV_TASK); /* Bluetooth��M���\�b�h�J�n */

	/* �����[�g�X�^�[�g���̓^�b�`�Z���T�[����X�^�[�g�M��������܂őҋ@ */
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
	Trigger_bt_close(); /* Bluetooth�ʐM�I�� */
}

/*
 * Bluetooth�ʐM�ڑ����\�b�h
 */
void Trigger_bt_connect() {
	bt_file = ev3_serial_open_file(EV3_SERIAL_BT);
	assert(bt_file != NULL);
}

/*
 * Bluetooth��M���\�b�h
 *
 * @param self �����̃|�C���^
 */
void Trigger_bt_recv_task(intptr_t unused) {
	while (1)
	{
		uint8_t c = fgetc(bt_file); /* ��M */
		switch (c)
		{
		case '1':
			bt_cmd = 1;
			break;
		default:
			break;
		}
		fputc(c, bt_file); /* �G�R�[�o�b�N */
	}
}

/*
 * Bluetooth�ʐM�I�����\�b�h
 */
void Trigger_bt_close() {
	fclose(bt_file); //�ڑ��I��
}