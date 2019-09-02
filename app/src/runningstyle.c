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
		linetrace->forward = 30;
		pidControl->kp = 0.84;
		pidControl->ki = 0.06;
		pidControl->kd = 0.033;
		break;
	case 1: /* �Z���2 */
		linetrace->forward = 140;
		pidControl->kp = 0.90;
		pidControl->ki = 0.06;
		pidControl->kd = 0.048;
		break;
	case 2: /* �Z���3 */
		linetrace->forward = 150;
		pidControl->kp = 1.04;
		pidControl->ki = 0.06;
		pidControl->kd = 0.068;
		break;
	case 3: /* �Z���4 */
		linetrace->forward = 200;
		pidControl->kp = 1.0;
		pidControl->ki = 0.06;
		pidControl->kd = 0.060;
		break;
	case 4: /* �Z���5 */
		linetrace->forward = 150;
		pidControl->kp = 1.1;
		pidControl->ki = 0.06;
		pidControl->kd = 0.060;
		break;
	case 5: /* ���6 */
		linetrace->forward = 120;
		pidControl->kp = 0.84;
		pidControl->ki = 0.06;
		pidControl->kd = 0.040;
		break;
	case 6: /* ���7 */
		linetrace->forward = 120;
		pidControl->kp = 1.04;
		pidControl->ki = 0.06;
		pidControl->kd = 0.062;
		break;
	case 7: /* ���8 */
		linetrace->forward = 150;
		pidControl->kp = 1.04;
		pidControl->ki = 0.06;
		pidControl->kd = 0.062;
		break;
	case 8: /* ���9 */
		linetrace->forward = 150;
		pidControl->kp = 0.92;
		pidControl->ki = 0.06;
		pidControl->kd = 0.047;
		break;
	case 9: /* ���10 */
		linetrace->forward = 150;
		pidControl->kp = 0.91;
		pidControl->ki = 0.06;
		pidControl->kd = 0.048;
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
		linetrace->forward = 200;
		pidControl->kp = 0.25;
		pidControl->ki = 0.03;
		pidControl->kd = 0.025;
		break;
	case 15: /* ���15 */
		linetrace->forward -= 2;
		if (linetrace->forward <= 0) {
			linetrace->forward = 0;
		}
		pidControl->kp = 0.25;
		pidControl->ki = 0.03;
		pidControl->kd = 0.025;
		break;
	default:
		linetrace->forward = 90;
		pidControl->kp = 0.80;
		pidControl->ki = 0.06;
		pidControl->kd = 0.030;
		break;
	}
}