#include "ev3api.h"
#include "runner.h"
#include "calibration.h"
//#include "run.h"

Calibration calibration;
//Run run;

/* モーターポート */
#define LEFT_MOTOR_P EV3_PORT_C
#define RIGHT_MOTOR_P EV3_PORT_B
#define TAIL_MOTOR_P EV3_PORT_A

/* センサーポート */
#define COLOR_SENSOR_P EV3_PORT_3
#define TOUCH_SENSOR_P EV3_PORT_1
#define GYRO_SENSOR_P EV3_PORT_4

/*
 * 初期化メソッド
 * 
 * @param self 自分のポインタ
 */
void Runner_init(Runner* self) {
	/* モーターポート設定 */
	ev3_motor_config(LEFT_MOTOR_P,LARGE_MOTOR);
	ev3_motor_config(RIGHT_MOTOR_P, LARGE_MOTOR);
	ev3_motor_config(TAIL_MOTOR_P, LARGE_MOTOR);

	/* センサーポート設定 */
	ev3_sensor_config(COLOR_SENSOR_P, COLOR_SENSOR);
	ev3_sensor_config(TOUCH_SENSOR_P, TOUCH_SENSOR);
	ev3_sensor_config(GYRO_SENSOR_P, GYRO_SENSOR);
}

void Runner_start(Runner* self) {
	/* キャリブレーション開始 */
	Calibration_init(&calibration);
	Calibration_start(&calibration);

	/* 走行開始 */
}