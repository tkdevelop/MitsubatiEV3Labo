#include "ev3api.h"
#include "runner.h"
#include "calibration.h"
#include "trigger.h"
#include "lcd.h"

Calibration calibration;
Trigger trigger;

/* ���[�^�[�|�[�g */
#define LEFT_MOTOR_P EV3_PORT_C
#define RIGHT_MOTOR_P EV3_PORT_B
#define TAIL_MOTOR_P EV3_PORT_A

/* �Z���T�[�|�[�g */
#define COLOR_SENSOR_P EV3_PORT_3
#define TOUCH_SENSOR_P EV3_PORT_1
#define GYRO_SENSOR_P EV3_PORT_4

/*
 * ���s�̏��������\�b�h
 * 
 * @param self �����̃|�C���^
 */
void Runner_init(Runner* self) {
	/* ���[�^�[�|�[�g�ݒ� */
	ev3_motor_config(LEFT_MOTOR_P, LARGE_MOTOR);
	ev3_motor_config(RIGHT_MOTOR_P, LARGE_MOTOR);
	ev3_motor_config(TAIL_MOTOR_P, LARGE_MOTOR);

	/* �Z���T�[�|�[�g�ݒ� */
	ev3_sensor_config(COLOR_SENSOR_P, COLOR_SENSOR);
	ev3_sensor_config(TOUCH_SENSOR_P, TOUCH_SENSOR);
	ev3_sensor_config(GYRO_SENSOR_P, GYRO_SENSOR);

	/* LCD��ʏ����� */
	Lcd_init();
}

/*
 * ���s�v���O�����J�n���\�b�h
 *
 * @param self �����̃|�C���^
 */
void Runner_start(Runner* self) {
	/* �L�����u���[�V�����J�n */
	Calibration_init(&calibration);
	Calibration_start(&calibration);

	/* ���s�ҋ@�J�n */
	Trigger_init(&trigger);
	Trigger_wait(&trigger);


}