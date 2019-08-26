#include "ev3api.h"
#include "runner.h"
#include "calibration.h"
#include "start.h"
#include "linetrace.h"
#include "battery.h"

Calibration calibration;
Linetrace linetrace;

/* ���[�^�|�[�g */
#define LEFT_MOTOR_P EV3_PORT_C
#define RIGHT_MOTOR_P EV3_PORT_B
#define TAIL_MOTOR_P EV3_PORT_A

/* �Z���T�|�[�g */
#define COLOR_SENSOR_P EV3_PORT_3
#define TOUCH_SENSOR_P EV3_PORT_1
#define GYRO_SENSOR_P EV3_PORT_4

/*
 * ���s�̏��������\�b�h
 *
 * @param self �����̃|�C���^
 */
void Runner_init() {
	/* ���[�^�|�[�g�ݒ� */
	ev3_motor_config(LEFT_MOTOR_P, LARGE_MOTOR);
	ev3_motor_config(RIGHT_MOTOR_P, LARGE_MOTOR);
	ev3_motor_config(TAIL_MOTOR_P, LARGE_MOTOR);

	/* �Z���T�|�[�g�ݒ� */
	ev3_sensor_config(COLOR_SENSOR_P, COLOR_SENSOR);
	ev3_sensor_config(TOUCH_SENSOR_P, TOUCH_SENSOR);
	ev3_sensor_config(GYRO_SENSOR_P, GYRO_SENSOR);

	/* LCD��ʏ����� */
	ev3_lcd_set_font(EV3_FONT_MEDIUM); /* �~�f�B�A���t�H���g */

	act_tsk(RUNNER_BATTERY_TASK); /* �o�b�e���c�ʕ\���^�X�N�J�n */
}

/*
 * ���s�v���O�����J�n���\�b�h
 *
 * @param self �����̃|�C���^
 */
void Runner_start() {
	/* �L�����u���[�V�����J�n */
	Calibration_init(&calibration);
	Calibration_start(&calibration);

	/* ���s�J�n */
	Start_init();
	Start_wait();
	Start_start();

	/* ���s */
	Linetrace_init(&linetrace,calibration.threshold);
	Linetrace_run(&linetrace);

	/* ���[�^�o�͒�~ */
	ev3_motor_stop(LEFT_MOTOR_P, false);
	ev3_motor_stop(RIGHT_MOTOR_P, false);
	ev3_motor_stop(TAIL_MOTOR_P, false);

	ter_tsk(RUNNER_BATTERY_TASK); /* �o�b�e���c�ʕ\���^�X�N�I�� */
}

/*
 * �o�b�e���c�ʕ\���^�X�N
 */
void Runner_battery_task() {
	while (1) {
		Battery_display(); /* �o�b�e���c�ʕ\�� */
	}
}