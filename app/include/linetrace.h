#ifndef _LINETRACE_H_
#define _LINETRACE_H_

typedef struct {
	int forward; /* �O�i�l */
}Linetrace;
void Linetrace_init(Linetrace* self,int threshold);
void Linetrace_run(Linetrace* self);

#endif