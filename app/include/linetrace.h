#ifndef _LINETRACE_H_
#define _LINETRACE_H_

typedef struct {
	int forward; /* 前進値 */
	int threshold; /* 閾値 */
	int lookup_threshold; /* ルックアップゲート攻略用閾値 */
}Linetrace;
void Linetrace_init(Linetrace* self,int threshold,int lookup_threshold);
void Linetrace_run(Linetrace* self);
void Linetrace_lookup(Linetrace* self);
void Linetrace_rotate(float angle);
void Linetrace_garage(Linetrace* self);
void Linetrace_timer_task();

#endif