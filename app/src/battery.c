#include "ev3api.h"
#include "battery.h"

/*
 * バッテリ残量表示メソッド
 */
void Battery_display() {
	int volt = Battery_get_voltage(); /* バッテリ電圧値を取得 */
	char m[20]; /* 画面出力用 */

	sprintf(m, "V :%4d/8395(%3d%%)", volt,(int)(volt * 0.0119118522930316)); /* 充電MAX時8395で換算して割合を表示 */
	ev3_lcd_draw_string(m, 0, 10);
}

/*
 * バッテリ電圧値取得メソッド
 *
 * return volt バッテリ電圧値
 */
int Battery_get_voltage() {
	int volt = ev3_battery_voltage_mV(); /* バッテリ電圧値を取得 */
	return volt;
}