#include "ev3api.h"
#include "gyrosensor.h"

#define GYRO_SENSOR_P EV3_PORT_4 /* �W���C���Z���T�\�|�[�g */

/*
 * �W���C���Z���T�\���Z�b�g���\�b�h
 */
void GyroSensor_reset() {
	ev3_gyro_sensor_reset(GYRO_SENSOR_P);
}

/*
 * �W���C���Z���T�\�p���x�擾���\�b�h
 *
 * return rate �p���x
 */
int16_t GyroSensor_get_rate() {
	int16_t rate = ev3_gyro_sensor_get_rate(GYRO_SENSOR_P);
	return rate;
}