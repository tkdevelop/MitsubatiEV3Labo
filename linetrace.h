#ifndef _LINETRACE_H_
#define _LINETRACE_H_

void Linetrace_init();
void Linetrace_run();
void backlash_cancel(signed char lpwm, signed char rpwm, int32_t *lenc, int32_t *renc);

#endif