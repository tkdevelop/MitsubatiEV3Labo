#ifndef _CALIBRATION_H_
#define _CALIBRATION_H_

typedef struct {
	int black, /* Ì½Ëõl */
		white, /* Ì½Ëõl */
		threshold; /* èl */
	int lookup_threshold; /* bNAbvQ[gUªpèl */
}Calibration;
void Calibration_init(Calibration* self);
void Calibration_start(Calibration* self);

#endif