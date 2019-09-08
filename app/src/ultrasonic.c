#include "ev3api.h"
#include "ultrasonic.h"

#define ULTRASONIC_SENSOR_P EV3_PORT_2

/*
 * �ԍ����擾���\�b�h
 *
 * @return distance ���b�N�A�b�v�Q�[�g�Ƃ̊ԍ���
 */
int16_t Ultrasonic_get_distance(){
	int16_t distance = (int)ev3_ultrasonic_sensor_get_distance(ULTRASONIC_SENSOR_P);
	return distance;
}

