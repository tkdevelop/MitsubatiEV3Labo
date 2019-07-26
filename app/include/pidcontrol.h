#ifndef _PIDCONTROL_H_
#define _PIDCONTROL_H_

typedef struct {
	float kp; /* �Q�C�� */
	float ki;
	float kd;
	float delta; /* ���� */
	float integral; /* �΍��̗ݐ� */
	float diff; /* �΍� */
	float diff_prev; /* �O��̕΍� */

	int threshold; /* 臒l */
}PidControl;
void PidControl_init(PidControl* self, int threshold);
float PidControl_calc(PidControl* self);

#endif