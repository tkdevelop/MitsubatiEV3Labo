#include "ev3api.h"
#include "calibration.h"
#include "tailcontrol.h"
#include "colorsensor.h"

#define TAIL_MOTOR_P EV3_PORT_A /* �e�[�����[�^�|�[�g */

#define TAIL_ANGLE_CALIB (-90) /* �L�����u���[�V�������e�[���p�x */
#define TAIL_ANGLE_STAND_UP_2 65 //87 /* ���b�N�A�b�v�U��-���S��~���̊p�x2

/*
 * �L�����u���[�V�������������\�b�h
 *
 * @param self �����̃|�C���^
 */
void Calibration_init(Calibration* self) {
	self->black = 2; /* ���A���A臒l��������*/
	self->white = 33;
	self->threshold = 17;
	self->lookup_threshold = 0;

	TailControl_reset(); /* �e�[�����[�^���Z�b�g */
	ColorSensor_init(); /* �J���[�Z���T�[������ */

	ev3_speaker_set_volume(1); /* ���ʐݒ� */
}

/*
 * �L�����u���[�V�����J�n���\�b�h
 *
 * @param self �����̃|�C���^
 */
void Calibration_start(Calibration* self) {
	ev3_led_set_color(LED_ORANGE); /* �L�����u���[�V�����J�n�ʒm */

	uint8_t reflect = 0; /* ���ˌ��l */
	char m[20]; /* ��ʏo�͗p */

	while (1) {
		TailControl_control(TAIL_ANGLE_CALIB); /* �e�[������ */

		reflect = ColorSensor_get_reflect(); /* ���ˌ��l�擾 */
		sprintf(m, "reflect : %2d", reflect);
		ev3_lcd_draw_string(m, 0, 30);

		if (ev3_button_is_pressed(LEFT_BUTTON)) { /* ���l�i�[ */
			self->black = reflect;
			sprintf(m, "black : %2d", self->black);
			ev3_lcd_draw_string(m, 0, 50);
		}
		else if (ev3_button_is_pressed(RIGHT_BUTTON)) { /* ���l�i�[ */
			self->white = reflect;
			sprintf(m, "white : %2d", self->white);
			ev3_lcd_draw_string(m, 0, 70);
		}
		else if (ev3_button_is_pressed(DOWN_BUTTON)) { /* 臒l�i�[ */
			self->threshold = (self->black + self->white) / 2;
			sprintf(m, "threshold : %2d", self->threshold);
			ev3_lcd_draw_string(m, 0, 90);
		}
		else if (ev3_button_is_pressed(ENTER_BUTTON)) { /* �L�����u���[�V�����I�� */
			ev3_speaker_play_tone(NOTE_C5, 1000);
			break;
		}
		tslp_tsk(4);
	}

	TailControl_reset(); /* �e�[�����[�^���Z�b�g */
	tslp_tsk(500);

	/* �e�[�������b�N�A�b�v�Q�[�g�U���p�ɉ����ăL�����u���[�V���� */
	while (1) {
		TailControl_control(TAIL_ANGLE_STAND_UP_2); /* �e�[������ */

		reflect = ColorSensor_get_reflect(); /* ���ˌ��l�擾 */
		sprintf(m, "reflect : %2d", reflect);
		ev3_lcd_draw_string(m, 0, 30);

		if (ev3_button_is_pressed(UP_BUTTON)) { /* ���b�N�A�b�v�Q�[�g�U���p臒l�i�[ */
			self->lookup_threshold = reflect * 10;
			sprintf(m, "lookup : %2d", self->lookup_threshold);
			ev3_lcd_draw_string(m, 0, 110);
		}
		else if (ev3_button_is_pressed(ENTER_BUTTON)) { /* �L�����u���[�V�����I�� */
			ev3_speaker_play_tone(NOTE_C5, 1000);
			break;
		}
		tslp_tsk(4);
	}

	TailControl_reset(); /* �e�[�����[�^���Z�b�g */
	tslp_tsk(500);

	/* �e�[����߂� */
	while (1) {
		TailControl_control(TAIL_ANGLE_CALIB); /* �e�[������ */

		if (ev3_button_is_pressed(ENTER_BUTTON)) { /* �L�����u���[�V�����I�� */
			ev3_speaker_play_tone(NOTE_C5, 1000);
			break;
		}
		tslp_tsk(4);
	}
}