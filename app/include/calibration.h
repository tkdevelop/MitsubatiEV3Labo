#ifndef _CALIBRATION_H_
#define _CALIBRATION_H_

typedef struct {
	int black, /* 黒の反射光値 */
		white, /* 白の反射光値 */
		threshold; /* 閾値 */
	int lookup_threshold; /* ルックアップゲート攻略用閾値 */
}Calibration;
void Calibration_init(Calibration* self);
void Calibration_start(Calibration* self);

#endif