#include "ev3api.h"
#include "balancer.h"
#include "balancecontrol.h"

/*
 * バックラッシュキャンセルメソッド
 *
 * @param lpwm 左モータPWM値(前回の出力値)
 * @param rpwm 右モータPWM値(前回の出力値)
 * @param lenc 左モータエンコーダ値
 * @param renc 右モータエンコーダ値
 */
void BalanceControl_backlash_cancel(signed char lpwm, signed char rpwm, int32_t *lenc, int32_t *renc) {
	const int BACKLASHHALF = 4;   // バックラッシュの半分[deg]

	if (lpwm < 0) *lenc += BACKLASHHALF;
	else if (lpwm > 0) *lenc -= BACKLASHHALF;

	if (rpwm < 0) *renc += BACKLASHHALF;
	else if (rpwm > 0) *renc -= BACKLASHHALF;
}

/*
 * バランスコントロール初期化メソッド
 *
 * @param self 自分のポインタ
 */
void BalanceControl_balance_init() {
	balance_init(); /* 倒立振子API初期化 */
}

/*
 * バランスコントロールメソッド
 *
 * @param forward 前進値
 * @param turn 旋回命令
 * @param gyro ジャイロセンサ値
 * @param GYRO_OFFSET ジャイロセンサオフセット値
 * @param motor_ang_l 左モータエンコーダ値
 * @param motor_ang_r 右モータエンコーダ値
 * @param volt バッテリ電圧値
 * @param pwm_L 左モータPWM出力値
 * @param pwm_R 右モータPWM出力値
 */
void BalanceControl_balance_control(float forward, float turn, float gyro,
float GYRO_OFFSET, float motor_ang_l, float motor_ang_r,
float volt, signed char *pwm_L, signed char *pwm_R) {
	balance_control(
		forward,
		turn,
		gyro,
		GYRO_OFFSET,
		motor_ang_l,
		motor_ang_r,
		volt,
		pwm_L,
		pwm_R); /* 左右モータ出力値を得る */
}