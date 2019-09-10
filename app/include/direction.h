#ifndef _DIRECTION_H_
#define _DIRECTION_H_

typedef struct {
	float direction; /* •ûˆÊ */
}Direction;
void Direction_init(Direction* self);
float Direction_calc(Direction* self,float distance_4ms_left,float distance_4ms_right);
void Direction_reset(Direction* self);

#endif