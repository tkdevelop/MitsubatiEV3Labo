#include "ev3api.h"
#include "linetrace.h"
#include "balancer.h"
#include "tailcontrol.h"

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
	ev3_motor_reset_counts(LEFT_MOTOR_P);
	ev3_motor_reset_counts(RIGHT_MOTOR_P);

	ev3_gyro_sensor_reset(GYRO_SENSOR_P); /* �W���C���Z���T�\���Z�b�g */

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
		motor_ang_l = ev3_motor_get_counts(LEFT_MOTOR_P);
		motor_ang_r = ev3_motor_get_counts(RIGHT_MOTOR_P);
		gyro = ev3_gyro_sensor_get_rate(GYRO_SENSOR_P);
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

		set_tire_motor(LEFT_MOTOR_P, pwm_L); /* ���[�^�[��~���̃u���[�L�ݒ� */
		set_tire_motor(RIGHT_MOTOR_P, pwm_R);
		
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

/* �^�C�����[�^�o�͐��� */
void set_tire_motor(motor_port_t port, int8_t pwm)
{
	if (0x00 == pwm)
	{
		/* PWM��0�ł���ꍇ�A���[�^��~ */
		ev3_motor_stop(port, true);
	}
	else
	{
		/* ���[�^�o�� */
		ev3_motor_set_power(port, (int)pwm);
	}
}