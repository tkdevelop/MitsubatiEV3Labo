#include "ev3api.h"
#include "app.h"
#include "runner.h"

#if defined(BUILD_MODULE)
#include "module_cfg.h"
#else
#include "kernel_cfg.h"
#endif

void main_task() {
	/* ���s�̃v���O�������s */
	Runner_init();
	Runner_start();

	ext_tsk(); //�A�v���P�[�V�����I��
}
