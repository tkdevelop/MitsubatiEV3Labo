#include "ev3api.h"
#include "touchsensor.h"

#define TOUCH_SENSOR_P EV3_PORT_1

bool_t TouchSensor_is_pressed() {
	if (ev3_touch_sensor_is_pressed(TOUCH_SENSOR_P)) {
		return true;
	}
	else {
		return false;
	}
}