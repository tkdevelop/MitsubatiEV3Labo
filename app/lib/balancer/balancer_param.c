/**
 *******************************************************************************
 **	ファイル名 : balancer_param.c
 **
 **	概要       : 倒立振子制御パラメーター
 **
 ** 注記       : 倒立振子制御パラメーターは制御特性に大きな影響を与えます。
 **
 *******************************************************************************
 **/

/*============================================================================
 * データ定義
 *===========================================================================*/
float A_D = 0.9F;	/* ローパスフィルタ係数(左右車輪の平均回転角度用) */
float A_R = 0.996F; /* ローパスフィルタ係数(左右車輪の目標平均回転角度用) */

/* 状態フィードバック係数
 * K_F[0]: 車輪回転角度係数
 * K_F[1]: 車体傾斜角度係数
 * K_F[2]: 車輪回転角速度係数
 * K_F[3]: 車体傾斜角速度係数
 */
float K_F[4] = {-0.86526F, -30.73965F, -1.14828F*0.70F, -2.29757F};  // m=0.05;R=0.05;M=0.79;W=0.177;D=0.08;H=0.140
float K_I = -0.44721F;   /* サーボ制御用積分フィードバック係数 */

float K_PHIDOT = 25.0F*2.75F; /* 車体目標旋回角速度係数 */
float K_THETADOT = 6.00F; /* モータ目標回転角速度係数 */

const float BATTERY_GAIN = 0.001089F;	/* PWM出力算出用バッテリ電圧補正係数 */
const float BATTERY_OFFSET = 0.625F;	/* PWM出力算出用バッテリ電圧補正オフセット */

/*****************************************************************************
 * 定数変更内容については下記サイトを参照してください. 20180224 東海地区 清水
 * 定数変更箇所の解説
 * http://bit.ly/2EN22ku
 */
/******************************** END OF FILE ********************************/
