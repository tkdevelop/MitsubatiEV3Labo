#include "ev3api.h"
#include "start.h"
#include "tailcontrol.h"

#define TAIL_MOTOR_P EV3_PORT_A /* �e�[�����[�^�[�|�[�g */
#define TOUCH_SENSOR_P EV3_PORT_1 /* �^�b�`�Z���T�[�|�[�g */

#define START_CMD 1 /* �����[�g�X�^�[�g�p�R�}���h */
static FILE* bt_file = NULL; /* �V���A���|�[�g�̃t�@�C�� */
static int bt_cmd = 0; /* ��M�����R�}���h */

#define TAIL_ANGLE_STAND_UP 95 /* ���S��~���̊p�x[�x] */
#define TAIL_ANGLE_START  (TAIL_ANGLE_STAND_UP + 3) /* �X�^�[�g���̊p�x */
#define START_DELAY_TIME  (15) /* �X�^�[�g�x������ */

/*
 * �X�^�[�g���������\�b�h
 */
void Start_init() {
	Start_bt_connect(); /* Bluetooth�ʐM�ڑ� */
	act_tsk(START_BT_RECV_TASK); /* Bluetooth��M���\�b�h�J�n */
}

/*
 * ���s�ҋ@���\�b�h
 */
void Start_wait() {
	ev3_motor_reset_counts(TAIL_MOTOR_P); /* �e�[�����[�^�[���Z�b�g */

	/* �����[�g�X�^�[�g���̓^�b�`�Z���T�[����X�^�[�g�M��������܂őҋ@ */
	while (1) {

		TailControl_control(TAIL_ANGLE_STAND_UP); /* �e�[�����[�^�[���� */

		if (bt_cmd == START_CMD) {
			break;
		}

		if (ev3_touch_sensor_is_pressed(TOUCH_SENSOR_P)) {
			break;
		}

		tslp_tsk(10);
	}

	ter_tsk(START_BT_RECV_TASK); /* Bluetooth�M����M�^�X�N�I�� */
	Start_bt_close(); /* Bluetooth�ʐM�I�� */
}

/*
 * ���s�J�n���\�b�h
 */
void Start_start() {
	int start_delay_counter = 0; /* �X�^�[�g�x���J�E���^ */

	/* �X�^�[�g�x�� */
	while (1) {
		TailControl_control(TAIL_ANGLE_START); /* �e�[�����[�^���� */

		start_delay_counter++;

		if (START_DELAY_TIME < start_delay_counter) {
			/* �X�^�[�g�x�����Ԍo�� */
			break;
		}

		tslp_tsk(10);
	}
}

/*
 * Bluetooth�ʐM�ڑ����\�b�h
 */
void Start_bt_connect() {
	bt_file = ev3_serial_open_file(EV3_SERIAL_BT);
	assert(bt_file != NULL);
}

/*
 * Bluetooth�M����M�^�X�N
 *
 * @param self �����̃|�C���^
 */
void Start_bt_recv_task(intptr_t unused) {
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
void Start_bt_close() {
	fclose(bt_file); //�ڑ��I��
}