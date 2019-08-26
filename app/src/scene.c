#include "ev3api.h"
#include "scene.h"

/*
 * 区間初期化メソッド
 *
 * @param self 自分のポインタ
 */
void Scene_init(Scene* self) {
	self->scene = 0; /* 区間を初期化 */

	ev3_speaker_set_volume(1); /* 音量設定 */
}

/*
 * 区間取得メソッド
 *
 * @param self 自分のポインタ
 * @param distance 走行距離
 */
int Scene_get_scene(Scene* self,float distance) {
	if (self->scene == 0 && distance >= 300) { /* 区間1 */
		ev3_speaker_play_tone(NOTE_C5, 1000);
		self->scene++;
	}
	else if (self->scene == 1 && distance >= 600) { /* 区間2 */
		ev3_speaker_play_tone(NOTE_C5, 1000);
		self->scene++;
	}
	else if (self->scene == 2 && distance >= 900) { /* 区間3 */
		ev3_speaker_play_tone(NOTE_C5, 1000);
		self->scene++;
	}
	else if (self->scene == 3 && distance >= 1200) { /* 区間4 */
		ev3_speaker_play_tone(NOTE_C5, 1000);
		self->scene++;
	}

	return self->scene;
}