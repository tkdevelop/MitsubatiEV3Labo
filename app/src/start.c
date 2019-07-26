#include "ev3api.h"
#include "start.h"
#include "tailcontrol.h"
#include "touchsensor.h"
#include "bluetooth.h"

Bluetooth bluetooth;

#define TAIL_MOTOR_P EV3_PORT_A /* �e�[�����[�^�|�[�g */

#define START_CMD 1 /* �����[�g�X�^�[�g�p�R�}���h */

#define TAIL_ANGLE_STAND_UP 100 /* ���S��~���̊p�x[�x] */
#define TAIL_ANGLE_START  (TAIL_ANGLE_STAND_UP + 2) /* �X�^�[�g���̊p�x */
#define START_DELAY_TIME  20 /* �X�^�[�g�x������ */

/*
 * �X�^�[�g���������\�b�h
 */
void Start_init() {
	Bluetooth_connect(&bluetooth); /* Bluetooth�ʐM�ڑ� */
	act_tsk(START_BLUETOOTH_TASK); /* Bluetooth��M���\�b�h�J�n */
}

/*
 * ���s�ҋ@���\�b�h
 */
void Start_wait() {
	ev3_motor_reset_counts(TAIL_MOTOR_P); /* �e�[�����[�^���Z�b�g */

	/* �����[�g�X�^�[�g���̓^�b�`�Z���T����X�^�[�g�M��������܂őҋ@ */
	while (1) {

		TailControl_control(TAIL_ANGLE_STAND_UP); /* �e�[�����[�^���� */

		if (bluetooth.bt_cmd == START_CMD) {
			break;
		}

		if (TouchSensor_is_pressed()) {
			break;
		}

		tslp_tsk(10);
	}

	ter_tsk(START_BLUETOOTH_TASK); /* Bluetooth�M����M�^�X�N�I�� */
	Bluetooth_disconnect(&bluetooth); /* Bluetooth�ʐM�I�� */
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
 * Bluetooth�ʐM�^�X�N
 */
void Start_bluetooth_task() {
	while (1) {
		Bluetooth_recv(&bluetooth);
	}
}