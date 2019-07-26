#include "ev3api.h"
#include "linetrace.h"
#include "balancecontrol.h"
#include "tailcontrol.h"
#include "wheelmotor.h"
#include "gyrosensor.h"
#include "pidcontrol.h"
#include "touchsensor.h"
#include "distance.h"
#include "direction.h"

PidControl pidControl;
Distance distance;
Direction direction;

/* ���[�^�|�[�g */
#define LEFT_MOTOR_P EV3_PORT_C
#define RIGHT_MOTOR_P EV3_PORT_B
#define TAIL_MOTOR_P EV3_PORT_A

#define GYRO_OFFSET  0          /* �W���C���Z���T�I�t�Z�b�g�l(�p���x0[deg/sec]��) */

#define TAIL_ANGLE_DRIVE      3 /* �o�����X���s���̊p�x */
#define FORWARD 40 /* �O�i�l */

void Linetrace_init(int threshold) {
	/* ���s���[�^�G���R�[�_���Z�b�g */
	WheelMotor_reset(LEFT_MOTOR_P);
	WheelMotor_reset(RIGHT_MOTOR_P);

	GyroSensor_reset(); /* �W���C���Z���T���Z�b�g */

	BalanceControl_balance_init(); /* �|���U�qAPI������ */

	PidControl_init(&pidControl, threshold); /* Pid���䏉���� */

	Distance_init(&distance); /* �����v������ */
	Direction_init(&direction,&distance); /* ���ʌv������ */
}

void Linetrace_run() {
	int forward = 60; /* �O�i�l */
	int turn = 0; /* ���񖽗� */
	signed char pwm_L, pwm_R; /* ���E���[�^PWM�o�͒l */
	int32_t motor_ang_l, motor_ang_r; /* ���E���[�^�G���R�[�_�l */
	int rate, /* �W���C���Z���T�l */
		volt;  /* �o�b�e���d�� */

	float distance_num = 0.0; /* ���s���� */
	float direction_num = 0.0; /* ���� */

	FILE *logfile = fopen("/log.txt", "w");

	/* 4msec�����ő��s */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON) || TouchSensor_is_pressed()) /* �o�b�N�{�^���ő��s�����I�� */
		{
			fclose(logfile);
			break;
		}

		TailControl_control(TAIL_ANGLE_DRIVE); /* �e�[������ */

		Distance_update(&distance); /* �����v���X�V */
		Direction_update(&direction); /* ���ʌv���X�V */

		distance_num = Distance_get_distance(&distance); /* ���s�����擾 */
		direction_num = Direction_get_direction(&direction); /* ���ʎ擾 */
		fprintf(logfile, "%lf : %lf\r\n", distance_num,direction_num);

		turn = PidControl_calc(&pidControl); /* PID�擾 */

		/* �|���U�q����API �ɓn���p�����[�^���擾���� */
		motor_ang_l = WheelMotor_get_angle(LEFT_MOTOR_P);
		motor_ang_r = WheelMotor_get_angle(RIGHT_MOTOR_P);
		rate = GyroSensor_get_rate();
		volt = ev3_battery_voltage_mV();

		BalanceControl_backlash_cancel(pwm_L, pwm_R, &motor_ang_l, &motor_ang_r); /* �o�b�N���b�V���L�����Z�� */

		/* �|���U�q����API���Ăяo���A�|�����s���邽�߂� */
		/* ���E���[�^�o�͒l�𓾂� */
		BalanceControl_balance_control(
			(float)forward,
			(float)turn,
			(float)rate,
			(float)GYRO_OFFSET,
			(float)motor_ang_l,
			(float)motor_ang_r,
			(float)volt,
			(signed char*)&pwm_L,
			(signed char*)&pwm_R);

		/* ���[�^��~���̃u���[�L�ݒ� */
		WheelMotor_set_tire_motor(LEFT_MOTOR_P, pwm_L);
		WheelMotor_set_tire_motor(RIGHT_MOTOR_P, pwm_R);

		tslp_tsk(4);
	}
}