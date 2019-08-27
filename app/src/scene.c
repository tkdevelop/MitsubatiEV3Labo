#include "ev3api.h"
#include "scene.h"

/*
 * 区間初期化メソッド
 *
 * @param self 自分のポインタ
 */
void Scene_init(Scene* self) {
	self->scene = 0; /* 区間を初期化 */

	ev3_speaker_set_volume(2); /* 音量設定 */
}

/*
 * 区間取得メソッド
 *
 * @param self 自分のポインタ
 * @param distance 走行距離
 */
int Scene_get_scene(Scene* self,float distance) {
	if (self->scene == 0 && distance >= 500) { /* 〇区間2到達 */
		ev3_speaker_play_tone(NOTE_C5, 300);
		self->scene++;
	}
	else if (self->scene == 1 && distance >= 1300) { /* 〇区間3到達 */
		ev3_speaker_play_tone(NOTE_C5, 300);
		self->scene++;
	}
	else if (self->scene == 2 && distance >= 1800) { /* 〇区間4到達 */
		ev3_speaker_play_tone(NOTE_C5, 300);
		self->scene++;
	}
	else if (self->scene == 3 && distance >= 2500) { /* 〇区間5到達 */
		ev3_speaker_play_tone(NOTE_C5, 300);
		self->scene++;
	}
	else if (self->scene == 4 && distance >= 2600) { /* 〇区間6到達 */
		ev3_speaker_play_tone(NOTE_C5, 300);
		self->scene++;
	}
	else if (self->scene == 5 && distance >= 3300) { /* 〇区間7到達 */
		ev3_speaker_play_tone(NOTE_C5, 300);
		self->scene++;
	}
	else if (self->scene == 6 && distance >= 3800) { /* 〇区間8到達 */
		ev3_speaker_play_tone(NOTE_C5, 300);
		self->scene++;
	}
	else if (self->scene == 7 && distance >= 4200) { /* 区間9到達 */
		ev3_speaker_play_tone(NOTE_C5, 300);
		self->scene++;
	}
	else if (self->scene == 8 && distance >= 4600) { /* 区間10到達 */
		ev3_speaker_play_tone(NOTE_C5, 300);
		self->scene++;
	}
	else if (self->scene == 9 && distance >= 5000) { /* 区間11到達 */
		ev3_speaker_play_tone(NOTE_C5, 300);
		self->scene++;
	}
	else if (self->scene == 10 && distance >= 6000) { /* ▲区間12到達 */
		ev3_speaker_play_tone(NOTE_C5, 300);
		self->scene++;
	}
	else if (self->scene == 11 && distance >= 3500) { /* 区間13到達 */
		ev3_speaker_play_tone(NOTE_C5, 300);
		self->scene++;
	}
	else if (self->scene == 12 && distance >= 3500) { /* 区間14到達 */
		ev3_speaker_play_tone(NOTE_C5, 300);
		self->scene++;
	}
	else if (self->scene == 13 && distance >= 3500) { /* 区間15到達 */
		ev3_speaker_play_tone(NOTE_C5, 300);
		self->scene++;
	}
	else if (self->scene == 14 && distance >= 3500) { /* 区間16到達 */
		ev3_speaker_play_tone(NOTE_C5, 300);
		self->scene++;
	}
	else if (self->scene == 15 && distance >= 3500) { /* 区間17到達 */
		ev3_speaker_play_tone(NOTE_C5, 300);
		self->scene++;
	}

	return self->scene;
}