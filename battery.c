#include "ev3api.h"
#include "battery.h"

/*
 * バッテリー残量表示メソッド
 */
void Battery_display() {
	int volt = Battery_get_voltage(); /* 電圧を取得 */
	char m[20]; /* 画面出力用 */

	sprintf(m, "battery : %d%%", (int)(volt * 0.0119760479041916)); /* MAX-Voltageを8350として%に換算 */
	ev3_lcd_draw_string(m, 0, 10);
}

/*
 * 電圧取得メソッド
 *
 * return volt 電圧
 */
int Battery_get_voltage() {
	int volt = ev3_battery_voltage_mV();
	return volt;
}