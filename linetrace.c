#include "ev3api.h"
#include "linetrace.h"
#include "balancer.h"
#include "tailcontrol.h"
#include "leftmotor.h"
#include "rightmotor.h"
#include "gyrosensor.h"

/* ���[�^�[�|�[�g */
#define LEFT_MOTOR_P EV3_PORT_C
#define RIGHT_MOTOR_P EV3_PORT_B
#define TAIL_MOTOR_P EV3_PORT_A

#define GYRO_SENSOR_P EV3_PORT_4 /* �W���C���Z���T�\�|�[�g */
#define GYRO_OFFSET  0          /* �W���C���Z���T�I�t�Z�b�g�l(�p���x0[deg/sec]��) */

#define TAIL_ANGLE_DRIVE      3 /* �o�����X���s���̊p�x */
#define FORWARD 40 /* �O�i�l */

void Linetrace_init() {
	/* ���s���[�^�[�G���R�[�_�\���Z�b�g */
	LeftMotor_reset();
	RightMotor_reset();

	GyroSensor_reset(); /* �W���C���Z���T�\���Z�b�g */

	balance_init(); /* �|���U�qAPI������ */
}

void Linetrace_run() {
	//TODO:pid
	int forward = 10;
	int turn = 0;
	signed char pwm_L, pwm_R; /* ���E���[�^�[PWM�o�� */

	int32_t motor_ang_l, motor_ang_r;
	int gyro, volt;

	/* 4msec�����ő��s */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON)) /* �o�b�N�{�^���ő��s�����I�� */
		{
			break;
		}

		TailControl_control(TAIL_ANGLE_DRIVE);

		/* �|���U�q����API �ɓn���p�����[�^�[���擾���� */
		motor_ang_l = LeftMotor_get_angle();
		motor_ang_r = RightMotor_get_angle();
		gyro = GyroSensor_get_rate();
		volt = ev3_battery_voltage_mV();

		backlash_cancel(pwm_L, pwm_R, &motor_ang_l, &motor_ang_r); /* �o�b�N���b�V���L�����Z�� */

		/* �|���U�q����API���Ăяo���A�|�����s���邽�߂� */
		/* ���E���[�^�[�o�͒l�𓾂� */
		balance_control(
			(float)forward,
			(float)turn,
			(float)gyro,
			(float)GYRO_OFFSET,
			(float)motor_ang_l,
			(float)motor_ang_r,
			(float)volt,
			(signed char*)&pwm_L,
			(signed char*)&pwm_R);

		/* ���[�^�[��~���̃u���[�L�ݒ� */
		LeftMotor_set_tire_motor(pwm_L);
		RightMotor_set_tire_motor(pwm_R);
		
		tslp_tsk(4);
	}
}

void backlash_cancel(signed char lpwm, signed char rpwm, int32_t *lenc, int32_t *renc)
{
	const int BACKLASHHALF = 4;   // �o�b�N���b�V���̔���[deg]

	if (lpwm < 0) *lenc += BACKLASHHALF;
	else if (lpwm > 0) *lenc -= BACKLASHHALF;

	if (rpwm < 0) *renc += BACKLASHHALF;
	else if (rpwm > 0) *renc -= BACKLASHHALF;
}