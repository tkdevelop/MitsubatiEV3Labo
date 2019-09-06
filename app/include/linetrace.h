#ifndef _LINETRACE_H_
#define _LINETRACE_H_

typedef struct {
	int forward; /* 前進値 */
	int threshold; /* 閾値 */
}Linetrace;
void Linetrace_init(Linetrace* self,int threshold);
void Linetrace_run(Linetrace* self);
void Linetrace_lookup(Linetrace* self);
void Linetrace_garage(Linetrace* self);
void Linetrace_timer_task();

#endif