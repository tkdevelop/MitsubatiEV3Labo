#include "ev3api.h"
#include "app.h"
#include "runner.h"

#if defined(BUILD_MODULE)
#include "module_cfg.h"
#else
#include "kernel_cfg.h"
#endif

void main_task() {
	/* 走行体プログラム実行 */
	Runner_init();
	Runner_start();

	ext_tsk(); //アプリケーション終了
}
