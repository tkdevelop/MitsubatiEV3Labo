#include "ev3api.h"
#include "touchsensor.h"

/* センサーポート */
#define TOUCH_SENSOR_P EV3_PORT_1

void TouchSensor_check_input(TouchSensor* self) {
	if (ev3_touch_sensor_is_pressed(TOUCH_SENSOR_P) == 1) {
		self->input = 1;
	}
	else {
		self->input = 0;
	}
}