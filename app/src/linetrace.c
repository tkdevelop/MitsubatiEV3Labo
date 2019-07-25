#include "ev3api.h"
#include "linetrace.h"
#include "balancecontrol.h"
#include "tailcontrol.h"
#include "leftmotor.h"
#include "rightmotor.h"
#include "gyrosensor.h"
#include "pid.h"
#include "touchsensor.h"

Pid pid;

/* ���[�^�|�[�g */
#define LEFT_MOTOR_P EV3_PORT_C
#define RIGHT_MOTOR_P EV3_PORT_B
#define TAIL_MOTOR_P EV3_PORT_A

#define GYRO_OFFSET  0          /* �W���C���Z���T�I�t�Z�b�g�l(�p���x0[deg/sec]��) */

#define TAIL_ANGLE_DRIVE      3 /* �o�����X���s���̊p�x */
#define FORWARD 40 /* �O�i�l */

void Linetrace_init(int threshold) {
	/* ���s���[�^�G���R�[�_���Z�b�g */
	LeftMotor_reset();
	RightMotor_reset();

	GyroSensor_reset(); /* �W���C���Z���T���Z�b�g */

	BalanceControl_balance_init(); /* �|���U�qAPI������ */

	Pid_init(&pid, threshold); /* Pid������ */
}

void Linetrace_run() {
	int forward = 70; /* �O�i�l */
	int turn = 0; /* ���񖽗� */
	signed char pwm_L, pwm_R; /* ���E���[�^PWM�o�͒l */
	int32_t motor_ang_l, motor_ang_r; /* ���E���[�^�G���R�[�_�l */
	int rate, /* �W���C���Z���T�l */
		volt;  /* �o�b�e���d�� */

	char m[20];
	FILE *logfile = fopen("/log.txt", "w");

	/* 4msec�����ő��s */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON) || TouchSensor_is_pressed()) /* �o�b�N�{�^���ő��s�����I�� */
		{
			fclose(logfile);
			break;
		}

		TailControl_control(TAIL_ANGLE_DRIVE); /* �e�[������ */

		turn = Pid_calc(&pid); /* PID�擾 */
		sprintf(m, "pid :%3d", turn);
		ev3_lcd_draw_string(m, 0, 110);
		fprintf(logfile, "%d\r\n", turn);

		/* �|���U�q����API �ɓn���p�����[�^���擾���� */
		motor_ang_l = LeftMotor_get_angle();
		motor_ang_r = RightMotor_get_angle();
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
		LeftMotor_set_tire_motor(pwm_L);
		RightMotor_set_tire_motor(pwm_R);

		tslp_tsk(4);
	}
}