#include "ev3api.h"
#include "colorsensor.h"

#define COLOR_SENSOR_P EV3_PORT_3

/*
 * �J���[�Z���T���������\�b�h
 */
void ColorSensor_init() {
	ev3_color_sensor_get_reflect(COLOR_SENSOR_P); /* ���˗����[�h */
}

/*
 * ���ˌ��l�擾���\�b�h
 *
 * return reflect ���ˌ��l
 */
uint8_t ColorSensor_get_reflect() {
	uint8_t reflect = ev3_color_sensor_get_reflect(COLOR_SENSOR_P);
	return reflect;
}