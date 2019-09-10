#include "ev3api.h"
#include "runningstyle.h"
#include "linetrace.h"
#include "pidcontrol.h"

/*
 * ���@�؂�ւ����\�b�h
 *
 * @param self �����̃|�C���^
 */
void RunningStyle_switch(int scene,Linetrace* linetrace,PidControl* pidControl) {
	switch (scene) {
	case 0: /* ���1 */
		linetrace->forward = 60;
		pidControl->kp = 0.78;
		pidControl->ki = 0.06;
		pidControl->kd = 0.040;
		break;
	case 1: /* �Z���2 */
		linetrace->forward = 120;
		pidControl->kp = 0.86;
		pidControl->ki = 0.06;
		pidControl->kd = 0.050;
		break;
	case 2: /* �Z���3 */
		linetrace->forward = 150;
		pidControl->kp = 1.40;
		pidControl->ki = 0.06;
		pidControl->kd = 0.084;
		break;
	case 3: /* �Z���4 */
		linetrace->forward = 180;
		pidControl->kp = 0.64;
		pidControl->ki = 0.06;
		pidControl->kd = 0.056;
		break;
	case 4: /* �Z���5 */
		linetrace->forward = 150;
		pidControl->kp = 1.40;
		pidControl->ki = 0.06;
		pidControl->kd = 0.084;
		break;
	case 5: /* ���6 */
		linetrace->forward = 120;
		pidControl->kp = 0.90;
		pidControl->ki = 0.06;
		pidControl->kd = 0.040;
		break;
	case 6: /* ���7 */
		linetrace->forward = 120;
		pidControl->kp = 1.45;
		pidControl->ki = 0.06;
		pidControl->kd = 0.084;
		break;
	case 7: /* ���8 */
		linetrace->forward = 130;
		pidControl->kp = 1.30;
		pidControl->ki = 0.06;
		pidControl->kd = 0.078;
		break;
	case 8: /* ���9 */
		linetrace->forward = 130;
		pidControl->kp = 1.0;
		pidControl->ki = 0.06;
		pidControl->kd = 0.048;
		break;
	case 9: /* ���10 */
		linetrace->forward = 150;
		pidControl->kp = 1.20;
		pidControl->ki = 0.06;
		pidControl->kd = 0.070;
		break;
	case 10: /* ���11 */
		linetrace->forward = 170;
		pidControl->kp = 0.94;
		pidControl->ki = 0.06;
		pidControl->kd = 0.048;
		break;
	case 11: /* ���12 */
		linetrace->forward = 150;
		pidControl->kp = 0.92;
		pidControl->ki = 0.06;
		pidControl->kd = 0.042;
		break;
	case 12: /* ���13 */
		linetrace->forward = 160;
		pidControl->kp = 0.96;
		pidControl->ki = 0.06;
		pidControl->kd = 0.048;
		break;
	case 13: /* ���14 */
		linetrace->forward = 90;
		pidControl->kp = 1.2;
		pidControl->ki = 0.06;
		pidControl->kd = 0.037;
		break;
	case 14: /* ���15 */
		linetrace->forward = 180;
		pidControl->kp = 0.25;
		pidControl->ki = 0.03;
		pidControl->kd = 0.025;
		break;
	case 15: /* ���15 �S�[����  */
		linetrace->forward = 45;
		pidControl->kp = 0.76;
		pidControl->ki = 0.06;
		pidControl->kd = 0.042;
		break;
	default:
		linetrace->forward = 90;
		pidControl->kp = 0.80;
		pidControl->ki = 0.06;
		pidControl->kd = 0.030;
		break;
	}
}