#include "ev3api.h"
#include "calibration.h"
#include "tailcontrol.h"
#include "colorsensor.h"

#define TAIL_MOTOR_P EV3_PORT_A /* テールモータポート */

#define TAIL_ANGLE_CALIB (-90) /* キャリブレーション時テール角度 */
#define TAIL_ANGLE_STAND_UP_2 75//65 /* ルックアップ攻略-完全停止時の角度2

/*
 * キャリブレーション初期化メソッド
 *
 * @param self 自分のポインタ
 */
void Calibration_init(Calibration* self) {
	self->black = 2; /* 黒、白、閾値を初期化*/
	self->white = 33;
	self->threshold = 17;
	self->lookup_threshold = 5;

	TailControl_reset(); /* テールモータリセット */
	ColorSensor_init(); /* カラーセンサー初期化 */

	ev3_speaker_set_volume(1); /* 音量設定 */
}

/*
 * キャリブレーション開始メソッド
 *
 * @param self 自分のポインタ
 */
void Calibration_start(Calibration* self) {
	ev3_led_set_color(LED_ORANGE); /* キャリブレーション開始通知 */

	uint8_t reflect = 0; /* 反射光値 */
	char m[20]; /* 画面出力用 */

	while (1) {
		TailControl_control(TAIL_ANGLE_CALIB); /* テール制御 */

		reflect = ColorSensor_get_reflect(); /* 反射光値取得 */
		sprintf(m, "reflect : %2d", reflect);
		ev3_lcd_draw_string(m, 0, 30);

		if (ev3_button_is_pressed(LEFT_BUTTON)) { /* 黒値格納 */
			self->black = reflect;
			sprintf(m, "black : %2d", self->black);
			ev3_lcd_draw_string(m, 0, 50);
		}
		else if (ev3_button_is_pressed(RIGHT_BUTTON)) { /* 白値格納 */
			self->white = reflect;
			sprintf(m, "white : %2d", self->white);
			ev3_lcd_draw_string(m, 0, 70);
		}
		else if (ev3_button_is_pressed(DOWN_BUTTON)) { /* 閾値格納 */
			self->threshold = (self->black + self->white) / 2;
			sprintf(m, "threshold : %2d", self->threshold);
			ev3_lcd_draw_string(m, 0, 90);
		}
		else if (ev3_button_is_pressed(ENTER_BUTTON)) { /* キャリブレーション終了 */
			ev3_speaker_play_tone(NOTE_C5, 1000);
			break;
		}
		tslp_tsk(4);
	}

	TailControl_reset(); /* テールモータリセット */
	tslp_tsk(500);

	/* テールをルックアップゲート攻略用に下げてキャリブレーション */
	while (1) {
		TailControl_control(TAIL_ANGLE_STAND_UP_2); /* テール制御 */

		reflect = ColorSensor_get_reflect(); /* 反射光値取得 */
		sprintf(m, "reflect : %2d", reflect);
		ev3_lcd_draw_string(m, 0, 30);

		if (ev3_button_is_pressed(UP_BUTTON)) { /* ルックアップゲート攻略用閾値格納 */
			self->lookup_threshold = reflect;
			sprintf(m, "lookup : %2d", self->lookup_threshold);
			ev3_lcd_draw_string(m, 0, 110);
		}
		else if (ev3_button_is_pressed(ENTER_BUTTON)) { /* キャリブレーション終了 */
			ev3_speaker_play_tone(NOTE_C5, 1000);
			break;
		}
		tslp_tsk(4);
	}

	TailControl_reset(); /* テールモータリセット */
	tslp_tsk(500);

	/* テールを戻す */
	while (1) {
		TailControl_control(TAIL_ANGLE_CALIB); /* テール制御 */

		if (ev3_button_is_pressed(ENTER_BUTTON)) { /* キャリブレーション終了 */
			ev3_speaker_play_tone(NOTE_C5, 1000);
			break;
		}
		tslp_tsk(4);
	}
}