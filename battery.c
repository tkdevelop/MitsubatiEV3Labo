#include "ev3api.h"
#include "battery.h"

/*
 * �o�b�e���[�c�ʕ\�����\�b�h
 */
void Battery_display() {
	int volt = Battery_get_voltage(); /* �d�����擾 */
	char m[20]; /* ��ʏo�͗p */

	sprintf(m, "battery : %d%%", (int)(volt * 0.0119760479041916)); /* MAX-Voltage��8350�Ƃ���%�Ɋ��Z */
	ev3_lcd_draw_string(m, 0, 10);
}

/*
 * �d���擾���\�b�h
 *
 * return volt �d��
 */
int Battery_get_voltage() {
	int volt = ev3_battery_voltage_mV();
	return volt;
}