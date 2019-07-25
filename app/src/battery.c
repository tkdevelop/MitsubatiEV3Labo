#include "ev3api.h"
#include "battery.h"

/*
 * �o�b�e���c�ʕ\�����\�b�h
 */
void Battery_display() {
	int volt = Battery_get_voltage(); /* �o�b�e���d���l���擾 */
	char m[20]; /* ��ʏo�͗p */

	sprintf(m, "battery :%3d%%", (int)(volt * 0.012453300124533));
	ev3_lcd_draw_string(m, 0, 10);
}

/*
 * �o�b�e���d���l�擾���\�b�h
 *
 * return volt �o�b�e���d���l
 */
int Battery_get_voltage() {
	int volt = ev3_battery_voltage_mV(); /* �o�b�e���d���l���擾 */
	return volt;
}