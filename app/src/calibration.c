#include "ev3api.h"
#include "calibration.h"
#include "tailcontrol.h"
#include "colorsensor.h"

#define TAIL_MOTOR_P EV3_PORT_A /* �e�[�����[�^�|�[�g */

#define TAIL_ANGLE_CALIB (-90) /* �L�����u���[�V�������e�[���p�x */

/*
 * �L�����u���[�V�������������\�b�h
 *
 * @param self �����̃|�C���^
 */
void Calibration_init(Calibration* self) {
	self->black = 0; /* ���A���A臒l��������*/
	self->white = 0;
	self->threshold = 0;

	TailControl_reset(); /* �e�[�����[�^���Z�b�g */
	ColorSensor_init(); /* �J���[�Z���T������ */
}

/*
 * �L�����u���[�V�����J�n���\�b�h
 *
 * @param self �����̃|�C���^
 */
void Calibration_start(Calibration* self) {
	ev3_led_set_color(LED_ORANGE); /* �L�����u���[�V�����J�n�ʒm */

	uint8_t reflect = -1; /* ���ˌ��l */
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
			ev3_speaker_set_volume(1);
			ev3_speaker_play_tone(NOTE_C5, 1000);
			break;
		}
		tslp_tsk(10);
	}

	TailControl_reset(); /* �e�[�����[�^���Z�b�g */

	tslp_tsk(500);
}