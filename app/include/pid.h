#ifndef _PID_H_
#define _PID_H_

typedef struct {
	float kp; /* �Q�C�� */
	float ki;
	float kd;
	float delta; /* ���� */
	float integral; /* �΍��̗ݐ� */
	float diff; /* �΍� */
	float diff_prev; /* �O��̕΍� */

	int threshold; /* 臒l */
}Pid;
void Pid_init(Pid* self, int threshold);
float Pid_calc(Pid* self);

#endif