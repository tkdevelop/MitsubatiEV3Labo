#ifndef _TOUCHSENSOR_H_
#define _TOUCHSENSOR_H_

typedef struct {
	int input; /* �^�b�`�Z���T�[���͐M�� */
}TouchSensor;
void TouchSensor_check_input(TouchSensor* self);

#endif