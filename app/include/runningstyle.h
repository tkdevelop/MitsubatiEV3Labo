#ifndef _RUNNINGSTYLE_H_
#define _RUNNINGSTYLE_H_

#include "linetrace.h"
#include "pidcontrol.h"

typedef struct {
	Linetrace* linetrace; /* ���s�N���X�|�C���^ */
	PidControl* pidControl; /* PID����N���X�|�C���^ */
}RunningStyle;
void RunningStyle_init(RunningStyle* self, Linetrace* linetrace, PidControl* pidControl);
void RunningStyle_switch(RunningStyle* self, int scene);

#endif