#include "ev3api.h"
#include "colorsensor.h"

#define COLOR_SENSOR_P EV3_PORT_3

/*
 * カラーセンサ初期化メソッド
 */
void ColorSensor_init() {
	ev3_color_sensor_get_reflect(COLOR_SENSOR_P); /* 反射率モード */
}

/*
 * 反射光値取得メソッド
 *
 * return reflect 反射光値
 */
uint8_t ColorSensor_get_reflect() {
	uint8_t reflect = ev3_color_sensor_get_reflect(COLOR_SENSOR_P);
	return reflect;
}