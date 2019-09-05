#ifndef _CLOCK_H_
#define _CLOCK_H_

typedef struct {
	int time;
}Clock;
void Clock_reset(Clock* self);
void Clock_time_countup(Clock* self);
int Clock_get_time(Clock* self);

#endif