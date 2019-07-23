#include "ev3api.h"
#include "calibration.h"
#include "tailcontrol.h"

#define TAIL_MOTOR_P EV3_PORT_A /* テールモーターポート */
#define COLOR_SENSOR_P EV3_PORT_3 /* カラーセンサーポート */

#define TAIL_ANGLE_CALIB (-90) /* キャリブレーション時テール角度 */

/*
 * キャリブレーション初期化メソッド
 *
 * @param self 自分のポインタ
 */
void Calibration_init(Calibration* self) {
	ev3_motor_reset_counts(TAIL_MOTOR_P); /* テールモーター初期化 */
	ev3_color_sensor_get_reflect(COLOR_SENSOR_P); /* 反射率モード初回起動 */
}

/*
 * キャリブレーション開始メソッド
 *
 * @param self 自分のポインタ
 */
void Calibration_start(Calibration* self) {
	int reflect = -1; /* 反射光値 */
	char m[20]; /* 画面出力用 */

	while (1) {
		TailControl_control(TAIL_ANGLE_CALIB); /* テール制御 */

		reflect = ev3_color_sensor_get_reflect(COLOR_SENSOR_P); /* 反射光値取得 */
		sprintf(m, "reflect : %d", reflect);
		ev3_lcd_draw_string(m, 0, 30);

		if (ev3_button_is_pressed(LEFT_BUTTON)) { /* 黒値格納 */
			self->black = reflect;
			sprintf(m, "black : %d", self->black);
			ev3_lcd_draw_string(m, 0, 50);
		}
		else if (ev3_button_is_pressed(RIGHT_BUTTON)) { /* 白値格納 */
			self->white = reflect;
			sprintf(m, "white : %d", self->white);
			ev3_lcd_draw_string(m, 0, 70);
		}
		else if (ev3_button_is_pressed(DOWN_BUTTON)) { /* 閾値格納 */
			self->threshold = (self->black + self->white) / 2;
			sprintf(m, "threshold : %d", self->threshold);
			ev3_lcd_draw_string(m, 0, 90);
		}
		else if (ev3_button_is_pressed(ENTER_BUTTON)) { /* キャリブレーション終了 */
			ev3_speaker_set_volume(1);
			ev3_speaker_play_tone(NOTE_C5, 1000);
			break;
		}
		tslp_tsk(10);
	}

	ev3_motor_reset_counts(TAIL_MOTOR_P); /* テールモーター初期化 */

	tslp_tsk(500);
}