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
	case 0: /* ‹æŠÔ1 */
		linetrace->forward = 30;
		pidControl->kp = 0.84;
		pidControl->ki = 0.06;
		pidControl->kd = 0.033;
		break;
	case 1: /* Z‹æŠÔ2 */
		linetrace->forward = 140;
		pidControl->kp = 0.90;
		pidControl->ki = 0.06;
		pidControl->kd = 0.048;
		break;
	case 2: /* Z‹æŠÔ3 */
		linetrace->forward = 150;
		pidControl->kp = 1.04;
		pidControl->ki = 0.06;
		pidControl->kd = 0.068;
		break;
	case 3: /* Z‹æŠÔ4 */
		linetrace->forward = 200;
		pidControl->kp = 1.0;
		pidControl->ki = 0.06;
		pidControl->kd = 0.060;
		break;
	case 4: /* Z‹æŠÔ5 */
		linetrace->forward = 150;
		pidControl->kp = 1.1;
		pidControl->ki = 0.06;
		pidControl->kd = 0.060;
		break;
	case 5: /* ‹æŠÔ6 */
		linetrace->forward = 120;
		pidControl->kp = 0.84;
		pidControl->ki = 0.06;
		pidControl->kd = 0.040;
		break;
	case 6: /* ‹æŠÔ7 */
		linetrace->forward = 120;
		pidControl->kp = 1.04;
		pidControl->ki = 0.06;
		pidControl->kd = 0.062;
		break;
	case 7: /* ‹æŠÔ8 */
		linetrace->forward = 150;
		pidControl->kp = 1.04;
		pidControl->ki = 0.06;
		pidControl->kd = 0.062;
		break;
	case 8: /* ‹æŠÔ9 */
		linetrace->forward = 150;
		pidControl->kp = 0.92;
		pidControl->ki = 0.06;
		pidControl->kd = 0.047;
		break;
	case 9: /* ‹æŠÔ10 */
		linetrace->forward = 150;
		pidControl->kp = 0.91;
		pidControl->ki = 0.06;
		pidControl->kd = 0.048;
		break;
	case 10: /* ‹æŠÔ11 */
		linetrace->forward = 170;
		pidControl->kp = 0.94;
		pidControl->ki = 0.06;
		pidControl->kd = 0.048;
		break;
	case 11: /* ‹æŠÔ12 */
		linetrace->forward = 150;
		pidControl->kp = 0.92;
		pidControl->ki = 0.06;
		pidControl->kd = 0.042;
		break;
	case 12: /* ‹æŠÔ13 */
		linetrace->forward = 160;
		pidControl->kp = 0.96;
		pidControl->ki = 0.06;
		pidControl->kd = 0.048;
		break;
	case 13: /* ‹æŠÔ14 */
		linetrace->forward = 90;
		pidControl->kp = 1.2;
		pidControl->ki = 0.06;
		pidControl->kd = 0.037;
		break;
	case 14: /* ‹æŠÔ15 */
		linetrace->forward = 200;
		pidControl->kp = 0.25;
		pidControl->ki = 0.03;
		pidControl->kd = 0.025;
		break;
	case 15: /* ‹æŠÔ15 */
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