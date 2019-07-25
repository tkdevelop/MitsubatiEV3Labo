#ifndef _PID_H_
#define _PID_H_

typedef struct {
	float kp; /* ƒQƒCƒ“ */
	float ki;
	float kd;
	float delta; /* üŠú */
	float integral; /* •Î·‚Ì—İÏ */
	float diff; /* •Î· */
	float diff_prev; /* ‘O‰ñ‚Ì•Î· */

	int threshold; /* è‡’l */
}Pid;
void Pid_init(Pid* self, int threshold);
float Pid_calc(Pid* self);

#endif