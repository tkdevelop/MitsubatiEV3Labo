#include "ev3api.h"
#include "runningstyle.h"
#include "linetrace.h"
#include "pidcontrol.h"

/*
 * ‘––@Ø‚è‘Ö‚¦ƒƒ\ƒbƒh
 *
 * @param self Ž©•ª‚Ìƒ|ƒCƒ“ƒ^
 */
void RunningStyle_switch(int scene,Linetrace* linetrace,PidControl* pidControl) {
	switch (scene) {
	case 0: /* Z‹æŠÔ1 */
		linetrace->forward = 100;
		pidControl->kp = 0.25;
		pidControl->ki = 0.03;
		pidControl->kd = 0.020;
		break;
	case 1: /* Z‹æŠÔ2 */
		linetrace->forward = 85;
		pidControl->kp = 0.80;
		pidControl->ki = 0.06;
		pidControl->kd = 0.033;
		break;
	case 2: /* Z‹æŠÔ3 */
		linetrace->forward = 100;
		pidControl->kp = 0.25;
		pidControl->ki = 0.03;
		pidControl->kd = 0.020;
		break;
	case 3: /* Z‹æŠÔ4 */
		linetrace->forward = 95;
		pidControl->kp = 0.80;
		pidControl->ki = 0.06;
		pidControl->kd = 0.029;
		break;
	case 4: /* ‹æŠÔ5 */
		linetrace->forward = 100;
		pidControl->kp = 0.42;
		pidControl->ki = 0.03;
		pidControl->kd = 0.027;
		break;
	case 5: /* ‹æŠÔ6 */
		linetrace->forward = 90;
		pidControl->kp = 0.80;
		pidControl->ki = 0.06;
		pidControl->kd = 0.029;
		break;
	case 6: /* ‹æŠÔ7 */
		linetrace->forward = 95;
		pidControl->kp = 0.80;
		pidControl->ki = 0.06;
		pidControl->kd = 0.025;
		break;
	case 7: /* ‹æŠÔ8 */
		linetrace->forward = 95;
		pidControl->kp = 0.80;
		pidControl->ki = 0.06;
		pidControl->kd = 0.027;
		break;
	case 8: /* ‹æŠÔ9 */
		linetrace->forward = 95;
		pidControl->kp = 0.25;
		pidControl->ki = 0.03;
		pidControl->kd = 0.025;
		break;
	case 9: /* ‹æŠÔ10 */
		linetrace->forward = 95;
		pidControl->kp = 0.80;
		pidControl->ki = 0.06;
		pidControl->kd = 0.027;
		break;
	case 10: /* ‹æŠÔ11 */
		linetrace->forward = 100;
		pidControl->kp = 0.25;
		pidControl->ki = 0.03;
		pidControl->kd = 0.025;
		break;
	case 11: /* ‹æŠÔ12 */
		linetrace->forward = 90;
		pidControl->kp = 0.80;
		pidControl->ki = 0.06;
		pidControl->kd = 0.027;
		break;
	case 12: /* ‹æŠÔ13 */
		linetrace->forward = 100;
		pidControl->kp = 0.25;
		pidControl->ki = 0.03;
		pidControl->kd = 0.025;
		break;
	case 13: /* ‹æŠÔ14 */
		linetrace->forward = 90;
		pidControl->kp = 0.80;
		pidControl->ki = 0.06;
		pidControl->kd = 0.029;
		break;
	case 14: /* ‹æŠÔ15 */
		linetrace->forward = 95;
		pidControl->kp = 0.80;
		pidControl->ki = 0.06;
		pidControl->kd = 0.027;
		break;
	case 15: /* ‹æŠÔ16 */
		linetrace->forward = 90;
		pidControl->kp = 0.80;
		pidControl->ki = 0.06;
		pidControl->kd = 0.027;
		break;
	case 16: /* ‹æŠÔ17 */
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