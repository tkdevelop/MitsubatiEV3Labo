#ifndef _CALIBRATION_H_
#define _CALIBRATION_H_

typedef struct {
	int black, /* •‚Ì”½ËŒõ’l */
		white, /* ”’‚Ì”½ËŒõ’l */
		threshold; /* è‡’l */
}Calibration;
void Calibration_init(Calibration* self);
void Calibration_start(Calibration* self);

#endif