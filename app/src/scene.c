#include "ev3api.h"
#include "scene.h"

/*
 * ��ԏ��������\�b�h
 *
 * @param self �����̃|�C���^
 */
void Scene_init(Scene* self) {
	self->scene = 0; /* ��Ԃ������� */

	ev3_speaker_set_volume(1); /* ���ʐݒ� */
}

/*
 * ��Ԏ擾���\�b�h
 *
 * @param self �����̃|�C���^
 * @param distance ���s����
 */
int Scene_get_scene(Scene* self,float distance) {
	if (self->scene == 0 && distance >= 300) { /* ���1 */
		ev3_speaker_play_tone(NOTE_C5, 1000);
		self->scene++;
	}
	else if (self->scene == 1 && distance >= 600) { /* ���2 */
		ev3_speaker_play_tone(NOTE_C5, 1000);
		self->scene++;
	}
	else if (self->scene == 2 && distance >= 900) { /* ���3 */
		ev3_speaker_play_tone(NOTE_C5, 1000);
		self->scene++;
	}
	else if (self->scene == 3 && distance >= 1200) { /* ���4 */
		ev3_speaker_play_tone(NOTE_C5, 1000);
		self->scene++;
	}

	return self->scene;
}