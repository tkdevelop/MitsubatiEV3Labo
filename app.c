#include "ev3api.h"
#include "app.h"
#include "runner.h"

#if defined(BUILD_MODULE)
#include "module_cfg.h"
#else
#include "kernel_cfg.h"
#endif

Runner runner;

void main_task(intptr_t exinf) {
	/* 走行体プログラム実行 */
	Runner_init(&runner);
	Runner_start(&runner);

	ext_tsk(); //アプリケーション終了
}
