#ifndef _TOUCHSENSOR_H_
#define _TOUCHSENSOR_H_

typedef struct {
	int input; /* タッチセンサー入力信号 */
}TouchSensor;
void TouchSensor_check_input(TouchSensor* self);

#endif