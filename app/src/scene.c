#include "ev3api.h"
#include "scene.h"

/*
 * ��ԏ��������\�b�h
 *
 * @param self �����̃|�C���^
 */
void Scene_init(Scene* self) {
	self->scene = 0; /* ��Ԃ������� */

	ev3_speaker_set_volume(2); /* ���ʐݒ� */
}

/*
 * ��Ԏ擾���\�b�h
 *
 * @param self �����̃|�C���^
 * @param distance ���s����
 */
int Scene_get_scene(Scene* self,float distance) {
	if (self->scene == 0 && distance >= 500) { /* �Z���2���B */
		ev3_speaker_play_tone(NOTE_C5, 300);
		self->scene++;
	}
	else if (self->scene == 1 && distance >= 1300) { /* �Z���3���B */
		ev3_speaker_play_tone(NOTE_C5, 300);
		self->scene++;
	}
	else if (self->scene == 2 && distance >= 1800) { /* �Z���4���B */
		ev3_speaker_play_tone(NOTE_C5, 300);
		self->scene++;
	}
	else if (self->scene == 3 && distance >= 2500) { /* �Z���5���B */
		ev3_speaker_play_tone(NOTE_C5, 300);
		self->scene++;
	}
	else if (self->scene == 4 && distance >= 2600) { /* �Z���6���B */
		ev3_speaker_play_tone(NOTE_C5, 300);
		self->scene++;
	}
	else if (self->scene == 5 && distance >= 3300) { /* �Z���7���B */
		ev3_speaker_play_tone(NOTE_C5, 300);
		self->scene++;
	}
	else if (self->scene == 6 && distance >= 3800) { /* �Z���8���B */
		ev3_speaker_play_tone(NOTE_C5, 300);
		self->scene++;
	}
	else if (self->scene == 7 && distance >= 4200) { /* ���9���B */
		ev3_speaker_play_tone(NOTE_C5, 300);
		self->scene++;
	}
	else if (self->scene == 8 && distance >= 4600) { /* ���10���B */
		ev3_speaker_play_tone(NOTE_C5, 300);
		self->scene++;
	}
	else if (self->scene == 9 && distance >= 5000) { /* ���11���B */
		ev3_speaker_play_tone(NOTE_C5, 300);
		self->scene++;
	}
	else if (self->scene == 10 && distance >= 6000) { /* �����12���B */
		ev3_speaker_play_tone(NOTE_C5, 300);
		self->scene++;
	}
	else if (self->scene == 11 && distance >= 3500) { /* ���13���B */
		ev3_speaker_play_tone(NOTE_C5, 300);
		self->scene++;
	}
	else if (self->scene == 12 && distance >= 3500) { /* ���14���B */
		ev3_speaker_play_tone(NOTE_C5, 300);
		self->scene++;
	}
	else if (self->scene == 13 && distance >= 3500) { /* ���15���B */
		ev3_speaker_play_tone(NOTE_C5, 300);
		self->scene++;
	}
	else if (self->scene == 14 && distance >= 3500) { /* ���16���B */
		ev3_speaker_play_tone(NOTE_C5, 300);
		self->scene++;
	}
	else if (self->scene == 15 && distance >= 3500) { /* ���17���B */
		ev3_speaker_play_tone(NOTE_C5, 300);
		self->scene++;
	}

	return self->scene;
}