#ifndef _LINETRACE_H_
#define _LINETRACE_H_

typedef struct {
	int forward; /* �O�i�l */
	int threshold; /* 臒l */
	int lookup_threshold; /* ���b�N�A�b�v�Q�[�g�U���p臒l */
}Linetrace;
void Linetrace_init(Linetrace* self,int threshold,int lookup_threshold);
void Linetrace_run(Linetrace* self);
void Linetrace_lookup(Linetrace* self);
void Linetrace_rotate(float angle);
void Linetrace_garage(Linetrace* self);
void Linetrace_timer_task();

#endif