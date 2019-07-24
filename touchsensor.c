#include "ev3api.h"
#include "touchsensor.h"

#define TOUCH_SENSOR_P EV3_PORT_1

/*
 * �^�b�`�Z���T�[�����m�F���\�b�h
 *
 * return is_pressed �^�b�`�Z���T�[���������ꂽ��
 */
bool_t TouchSensor_is_pressed() {
	bool_t is_pressed = ev3_touch_sensor_is_pressed(TOUCH_SENSOR_P);
	return is_pressed;
}