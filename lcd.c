#include "ev3api.h"
#include "lcd.h"

/*
 * 画面初期化メソッド
 */
void Lcd_init() {
	ev3_lcd_set_font(EV3_FONT_MEDIUM); //フォント設定
}