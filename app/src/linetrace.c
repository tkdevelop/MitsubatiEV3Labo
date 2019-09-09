#include "ev3api.h"
#include "linetrace.h"
#include "balancecontrol.h"
#include "tailcontrol.h"
#include "wheelmotor.h"
#include "gyrosensor.h"
#include "pidcontrol.h"
#include "touchsensor.h"
#include "distance.h"
#include "scene.h"
#include "runningstyle.h"
#include "ultrasonic.h"
#include "clock.h"
#include "colorsensor.h"

PidControl pidControl;
Distance distance;
Scene scene;
Clock clock;

/* ���[�^�|�[�g */
#define LEFT_MOTOR_P EV3_PORT_C
#define RIGHT_MOTOR_P EV3_PORT_B
#define TAIL_MOTOR_P EV3_PORT_A

#define GYRO_OFFSET  0          /* �W���C���Z���T�I�t�Z�b�g�l(�p���x0[deg/sec]��) */
#define GYRO_OFFSET_LOOKUP (-20)		/* ���b�N�A�b�v�Q�[�g�U���p�W���C���Z���T�I�t�Z�b�g�l */

#define TAIL_ANGLE_DRIVE      3 /* �o�����X���s���̊p�x */
#define TAIL_ANGLE_STAND_UP_1	  90//87  /* ���b�N�A�b�v�U��-���S��~���̊p�x1 */
#define TAIL_ANGLE_STAND_UP_2	  87//75  /* ���b�N�A�b�v�U��-���S��~���̊p�x2 */

void Linetrace_init(Linetrace* self, int threshold,int lookup_threshold) {
	self->forward = 0; /* �O�i�l������ */
	self->threshold = threshold; /* 臒l�i�[ */
	self->lookup_threshold = lookup_threshold; /* ���b�N�A�b�v�Q�[�g�U���p臒l */

	/* ���s���[�^�G���R�[�_���Z�b�g */
	WheelMotor_reset(LEFT_MOTOR_P);
	WheelMotor_reset(RIGHT_MOTOR_P);

	GyroSensor_reset(); /* �W���C���Z���T���Z�b�g */

	BalanceControl_balance_init(); /* �|���U�qAPI������ */

	PidControl_init(&pidControl, self->threshold); /* Pid���䏉���� */

	Distance_init(&distance); /* ���Ȉʒu���菉���� */

	Scene_init(&scene); /* ��ԏ����� */
}

void Linetrace_run(Linetrace* self) {
	int turn = 0; /* ���񖽗� */
	signed char pwm_L, pwm_R; /* ���E���[�^PWM�o�͒l */
	int32_t motor_ang_l, motor_ang_r; /* ���E���[�^�G���R�[�_�l */
	int rate, /* �W���C���Z���T�l */
		volt;  /* �o�b�e���d�� */

	float distance_num = 0.0; /* ���s���� */
	int16_t ultrasonic_distance_num = 0; /* ���b�N�A�b�v�Q�[�g�܂ł̋��� */

	int scene_num = -1; /* ���s��� */

	/* 4msec�����ő��s */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON)) /* �o�b�N�{�^���ő��s�����I�� */
		{
			break;
		}

		TailControl_control(TAIL_ANGLE_DRIVE); /* �e�[������ */

		distance_num = Distance_calc(&distance); /* ���s�����v�Z */

		scene_num = Scene_get_scene(&scene, distance_num); /* ���s��Ԃ��擾 */

		ultrasonic_distance_num = Ultrasonic_get_distance(); /* ���b�N�A�b�v�Q�[�g�܂ł̋������擾 */
		if (8 > ultrasonic_distance_num) { /* ���b�N�A�b�v�Q�[�g��8cm��O�ɓ��B�����烋�[�v�𔲂��� */
			break;
		}

		RunningStyle_switch(scene_num, self, &pidControl); /* ���@�؂�ւ� */

		turn = PidControl_calc(&pidControl); /* ����ʎ擾 */

		/* �|���U�q����API �ɓn���p�����[�^���擾���� */
		motor_ang_l = WheelMotor_get_angle(LEFT_MOTOR_P);
		motor_ang_r = WheelMotor_get_angle(RIGHT_MOTOR_P);
		rate = GyroSensor_get_rate();
		volt = ev3_battery_voltage_mV();

		BalanceControl_backlash_cancel(pwm_L, pwm_R, &motor_ang_l, &motor_ang_r); /* �o�b�N���b�V���L�����Z�� */

		/* �|���U�q����API���Ăяo���A�|�����s���邽�߂� */
		/* ���E���[�^�o�͒l�𓾂� */
		BalanceControl_balance_control(
			(float)self->forward,
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

void Linetrace_lookup(Linetrace* self) {
	int turn = 0; /* ���񖽗� */
	signed char pwm_L, pwm_R; /* ���E���[�^PWM�o�͒l */
	int32_t motor_ang_l, motor_ang_r; /* ���E���[�^�G���R�[�_�l */
	int rate, /* �W���C���Z���T�l */
		volt;  /* �o�b�e���d�� */

	float distance_num = 0.0; /* ���s���� */

	int time = 0; /* �^�C�� */
	act_tsk(LINETRACE_TIMER_TASK); /* �^�C�}�[�^�X�N�J�n */

	int scene_num = -1; /* ���s��� */
	/* �e�[�������낷 */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON)) /* �o�b�N�{�^���ő��s�����I�� */
		{
			break;
		}

		TailControl_control(TAIL_ANGLE_STAND_UP_1); /* �e�[������ */

		distance_num = Distance_calc(&distance); /* ���s�����v�Z */

		scene_num = Scene_get_scene(&scene, distance_num); /* ���s��Ԃ��擾 */

		time = Clock_get_time(&clock); /* �^�C���擾 */
		if (time > 200) { /* ���̊ԃe�[�������� */
			break;
		}
		else {

			RunningStyle_switch(scene_num, self, &pidControl); /* ���@�؂�ւ� */

			turn = PidControl_calc(&pidControl); /* ����ʎ擾 */

			/* �|���U�q����API �ɓn���p�����[�^���擾���� */
			motor_ang_l = WheelMotor_get_angle(LEFT_MOTOR_P);
			motor_ang_r = WheelMotor_get_angle(RIGHT_MOTOR_P);
			rate = GyroSensor_get_rate();
			volt = ev3_battery_voltage_mV();

			BalanceControl_backlash_cancel(pwm_L, pwm_R, &motor_ang_l, &motor_ang_r); /* �o�b�N���b�V���L�����Z�� */

			/* �|���U�q����API���Ăяo���A�|�����s���邽�߂� */
			/* ���E���[�^�o�͒l�𓾂� */
			BalanceControl_balance_control(
				(float)self->forward,
				(float)turn,
				(float)rate,
				(float)GYRO_OFFSET_LOOKUP,
				(float)motor_ang_l,
				(float)motor_ang_r,
				(float)volt,
				(signed char*)&pwm_L,
				(signed char*)&pwm_R);

			/* ���[�^��~���̃u���[�L�ݒ� */
			WheelMotor_set_tire_motor(LEFT_MOTOR_P, pwm_L);
			WheelMotor_set_tire_motor(RIGHT_MOTOR_P, pwm_R);
		}

		tslp_tsk(4);
	}
	ter_tsk(LINETRACE_TIMER_TASK); /* �^�C�}�[�^�X�N�I�� */

	Clock_reset(&clock); /* �^�C�}�[���Z�b�g */
	act_tsk(LINETRACE_TIMER_TASK); /* �^�C�}�[�^�X�N�J�n */

	uint8_t reflect = 0; /* ���ˌ��l */

	/* ���b�N�A�b�v�Q�[�g���ԑ̂��ʂ�߂���܂őO�i�E��i������ */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON)) /* �o�b�N�{�^���ő��s�����I�� */
		{
			break;
		}

		TailControl_control(TAIL_ANGLE_STAND_UP_2); /* �e�[������ */

		turn = 50;
		
		reflect = ColorSensor_get_reflect(); /* ���ˌ��l���擾 */
		//reflect *= 4; /* �J���[�Z���T�[���X�����␳ */

		if (reflect > self->lookup_threshold) { /* ����ʂ��}�C�i�X�ɐݒ� */
			turn = -turn;
		}

		time = Clock_get_time(&clock); /* �^�C���擾 */
		if (time < 2200) {
			ev3_motor_steer(LEFT_MOTOR_P, RIGHT_MOTOR_P, 10, turn); /* ���s�̂�O�i */
		}
		else if (time < 3500) {
			ev3_motor_set_power(LEFT_MOTOR_P, -10); /* ���s�̂�180�x��] */
			ev3_motor_set_power(RIGHT_MOTOR_P, 10);
		}
		else if (time < 7400) {
			ev3_motor_steer(LEFT_MOTOR_P, RIGHT_MOTOR_P, 10, turn); /* ���s�̂�O�i */
		}
		else if (time < 8800) {
			ev3_motor_set_power(LEFT_MOTOR_P, -10); /* ���s�̂�180�x��] */
			ev3_motor_set_power(RIGHT_MOTOR_P, 10);
		}
		else if (time < 15000) {
			ev3_motor_steer(LEFT_MOTOR_P, RIGHT_MOTOR_P, 10, turn); /* ���s�̂�O�i */
		}
		else {
			break;
		}

		tslp_tsk(4);
	}
	ter_tsk(LINETRACE_TIMER_TASK); /* �^�C�}�[�^�X�N�I�� */
}

void Linetrace_garage(Linetrace* self) {
	colorid_t color = 0;
	int turn = -50;
	int time = 0;

	Clock_reset(&clock); /* �^�C�}�[���Z�b�g */
	act_tsk(LINETRACE_TIMER_TASK); /* �^�C�}�[�^�X�N�J�n */

	/* �̃��C����T�� */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON)) /* �o�b�N�{�^���ő��s�����I�� */
		{
			break;
		}

		TailControl_control(TAIL_ANGLE_STAND_UP_2); /* �e�[������ */

		color = ColorSensor_get_color(); /* �J���[�擾 */
		if (color == 2) { /* �̃��C���ɓ��B�����烋�[�v�𔲂��� */
			break;
		}

		time = Clock_get_time(&clock); /* �^�C���擾 */
		if (700 < time) {
			turn = -turn;

			ter_tsk(LINETRACE_TIMER_TASK); /* �^�C�}�[�^�X�N�I�� */
			Clock_reset(&clock); /* �^�C�}�[���Z�b�g */
			act_tsk(LINETRACE_TIMER_TASK); /* �^�C�}�[�^�X�N�J�n */
		}

		ev3_motor_steer(LEFT_MOTOR_P, RIGHT_MOTOR_P, 10, turn); /* ���s�̂�O�i */

		tslp_tsk(4);
	}
}

/*
 * �^�C�}�[�^�X�N
 */
void Linetrace_timer_task() {
	while (1) {
		Clock_time_countup(&clock);
		tslp_tsk(1);
	}
}