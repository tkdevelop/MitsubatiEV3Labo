#include "ev3api.h"
#include "colorsensor.h"

#define COLOR_SENSOR_P EV3_PORT_3

/*
 * ���ˌ��l�擾���\�b�h
 *
 * return reflect ���ˌ��l
 */
uint8_t ColorSensor_get_reflect() {
	uint8_t reflect = ev3_color_sensor_get_reflect(COLOR_SENSOR_P);
	return reflect;
}

/*
 * �J���[�擾���\�b�h
 *
 * return color �J���[
 */
colorid_t ColorSensor_get_color() {
	colorid_t color = ev3_color_sensor_get_color(COLOR_SENSOR_P);
	return color;
}