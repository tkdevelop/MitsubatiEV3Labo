#ifndef _PIDCONTROL_H_
#define _PIDCONTROL_H_

typedef struct {
	float kp; /* ƒQƒCƒ“ */
	float ki;
	float kd;
	float delta; /* üŠú */
	float integral; /* •Î·‚Ì—İÏ */
	float diff; /* •Î· */
	float diff_prev; /* ‘O‰ñ‚Ì•Î· */

	int threshold; /* è‡’l */
}PidControl;
void PidControl_init(PidControl* self, int threshold);
float PidControl_calc(PidControl* self);

#endif