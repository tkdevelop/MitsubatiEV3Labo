#include "ev3api.h"
#include "tailmotor.h"

#define TAIL_MOTOR_P EV3_PORT_A /* �e�[�����[�^�[�|�[�g */

#define P_GAIN             2.5F /* ���S��~�p���[�^�[������W�� */
#define PWM_ABS_MAX          60 /* ���S��~�p���[�^�[����PWM��΍ő�l */

/*
 * �e�[���쓮���\�b�h
 */
void TailMotor_control(signed int angle) {
	signed int pwm = (signed int)((angle - ev3_motor_get_counts(TAIL_MOTOR_P))*P_GAIN); /* ��ᐧ�� */
	
	/* PWM�o�͖O�a���� */
	if (pwm > PWM_ABS_MAX)
	{
		pwm = PWM_ABS_MAX;
	}
	else if (pwm < -PWM_ABS_MAX)
	{
		pwm = -PWM_ABS_MAX;
	}

	if (pwm == 0)
	{
		ev3_motor_stop(TAIL_MOTOR_P, true);
	}
	else
	{
		ev3_motor_set_power(TAIL_MOTOR_P, (signed char)pwm);
	}
}