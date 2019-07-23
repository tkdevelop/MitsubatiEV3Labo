#include "ev3api.h"
#include "calibration.h"
#include "tailcontrol.h"

#define TAIL_MOTOR_P EV3_PORT_A /* �e�[�����[�^�[�|�[�g */
#define COLOR_SENSOR_P EV3_PORT_3 /* �J���[�Z���T�[�|�[�g */

#define TAIL_ANGLE_CALIB (-90) /* �L�����u���[�V�������e�[���p�x */

/*
 * �L�����u���[�V�������������\�b�h
 *
 * @param self �����̃|�C���^
 */
void Calibration_init(Calibration* self) {
	ev3_motor_reset_counts(TAIL_MOTOR_P); /* �e�[�����[�^�[������ */
	ev3_color_sensor_get_reflect(COLOR_SENSOR_P); /* ���˗����[�h����N�� */
}

/*
 * �L�����u���[�V�����J�n���\�b�h
 *
 * @param self �����̃|�C���^
 */
void Calibration_start(Calibration* self) {
	int reflect = -1; /* ���ˌ��l */
	char m[20]; /* ��ʏo�͗p */

	while (1) {
		TailControl_control(TAIL_ANGLE_CALIB); /* �e�[������ */

		reflect = ev3_color_sensor_get_reflect(COLOR_SENSOR_P); /* ���ˌ��l�擾 */
		sprintf(m, "reflect : %d", reflect);
		ev3_lcd_draw_string(m, 0, 30);

		if (ev3_button_is_pressed(LEFT_BUTTON)) { /* ���l�i�[ */
			self->black = reflect;
			sprintf(m, "black : %d", self->black);
			ev3_lcd_draw_string(m, 0, 50);
		}
		else if (ev3_button_is_pressed(RIGHT_BUTTON)) { /* ���l�i�[ */
			self->white = reflect;
			sprintf(m, "white : %d", self->white);
			ev3_lcd_draw_string(m, 0, 70);
		}
		else if (ev3_button_is_pressed(DOWN_BUTTON)) { /* 臒l�i�[ */
			self->threshold = (self->black + self->white) / 2;
			sprintf(m, "threshold : %d", self->threshold);
			ev3_lcd_draw_string(m, 0, 90);
		}
		else if (ev3_button_is_pressed(ENTER_BUTTON)) { /* �L�����u���[�V�����I�� */
			ev3_speaker_set_volume(1);
			ev3_speaker_play_tone(NOTE_C5, 1000);
			break;
		}
		tslp_tsk(10);
	}

	ev3_motor_reset_counts(TAIL_MOTOR_P); /* �e�[�����[�^�[������ */

	tslp_tsk(500);
}