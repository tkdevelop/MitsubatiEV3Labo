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
	case 0: /* �Z���1 */
		linetrace->forward = 100;
		pidControl->kp = 0.25;
		pidControl->ki = 0.03;
		pidControl->kd = 0.020;
		break;
	case 1: /* �Z���2 */
		linetrace->forward = 85;
		pidControl->kp = 0.80;
		pidControl->ki = 0.06;
		pidControl->kd = 0.033;
		break;
	case 2: /* �Z���3 */
		linetrace->forward = 100;
		pidControl->kp = 0.25;
		pidControl->ki = 0.03;
		pidControl->kd = 0.020;
		break;
	case 3: /* �Z���4 */
		linetrace->forward = 95;
		pidControl->kp = 0.80;
		pidControl->ki = 0.06;
		pidControl->kd = 0.029;
		break;
	case 4: /* ���5 */
		linetrace->forward = 100;
		pidControl->kp = 0.42;
		pidControl->ki = 0.03;
		pidControl->kd = 0.027;
		break;
	case 5: /* ���6 */
		linetrace->forward = 90;
		pidControl->kp = 0.80;
		pidControl->ki = 0.06;
		pidControl->kd = 0.029;
		break;
	case 6: /* ���7 */
		linetrace->forward = 95;
		pidControl->kp = 0.80;
		pidControl->ki = 0.06;
		pidControl->kd = 0.025;
		break;
	case 7: /* ���8 */
		linetrace->forward = 95;
		pidControl->kp = 0.80;
		pidControl->ki = 0.06;
		pidControl->kd = 0.027;
		break;
	case 8: /* ���9 */
		linetrace->forward = 95;
		pidControl->kp = 0.25;
		pidControl->ki = 0.03;
		pidControl->kd = 0.025;
		break;
	case 9: /* ���10 */
		linetrace->forward = 95;
		pidControl->kp = 0.80;
		pidControl->ki = 0.06;
		pidControl->kd = 0.027;
		break;
	case 10: /* ���11 */
		linetrace->forward = 100;
		pidControl->kp = 0.25;
		pidControl->ki = 0.03;
		pidControl->kd = 0.025;
		break;
	case 11: /* ���12 */
		linetrace->forward = 90;
		pidControl->kp = 0.80;
		pidControl->ki = 0.06;
		pidControl->kd = 0.027;
		break;
	case 12: /* ���13 */
		linetrace->forward = 100;
		pidControl->kp = 0.25;
		pidControl->ki = 0.03;
		pidControl->kd = 0.025;
		break;
	case 13: /* ���14 */
		linetrace->forward = 90;
		pidControl->kp = 0.80;
		pidControl->ki = 0.06;
		pidControl->kd = 0.029;
		break;
	case 14: /* ���15 */
		linetrace->forward = 95;
		pidControl->kp = 0.80;
		pidControl->ki = 0.06;
		pidControl->kd = 0.027;
		break;
	case 15: /* ���16 */
		linetrace->forward = 90;
		pidControl->kp = 0.80;
		pidControl->ki = 0.06;
		pidControl->kd = 0.027;
		break;
	case 16: /* ���17 */
		linetrace->forward -= 5;
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