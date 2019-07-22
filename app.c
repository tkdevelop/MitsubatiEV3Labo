#include "ev3api.h"
#include "app.h"

#if defined(BUILD_MODULE)
#include "module_cfg.h"
#else
#include "kernel_cfg.h"
#endif

void main_task(intptr_t exinf) {
	ext_tsk(); //アプリケーション終了
}
