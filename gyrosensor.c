#include "ev3api.h"
#include "gyrosensor.h"

#define GYRO_SENSOR_P EV3_PORT_4 /* ジャイロセンサ―ポート */

/*
 * ジャイロセンサ―リセットメソッド
 */
void GyroSensor_reset() {
	ev3_gyro_sensor_reset(GYRO_SENSOR_P);
}

/*
 * ジャイロセンサ―角速度取得メソッド
 *
 * return rate 角速度
 */
int16_t GyroSensor_get_rate() {
	int16_t rate = ev3_gyro_sensor_get_rate(GYRO_SENSOR_P);
	return rate;
}