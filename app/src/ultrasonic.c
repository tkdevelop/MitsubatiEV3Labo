#include "ev3api.h"
#include "ultrasonic.h"

#define ULTRASONIC_SENSOR_P EV3_PORT_2

/*
 * 間合い取得メソッド
 *
 * @return distance ルックアップゲートとの間合い
 */
int16_t Ultrasonic_get_distance(){
	int16_t distance = (int)ev3_ultrasonic_sensor_get_distance(ULTRASONIC_SENSOR_P);
	return distance;
}

