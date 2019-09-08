#ifndef _CALIBRATION_H_
#define _CALIBRATION_H_

typedef struct {
	int black, /* ���̔��ˌ��l */
		white, /* ���̔��ˌ��l */
		threshold; /* 臒l */
	int lookup_threshold; /* ���b�N�A�b�v�Q�[�g�U���p臒l */
}Calibration;
void Calibration_init(Calibration* self);
void Calibration_start(Calibration* self);

#endif