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
#include "direction.h"

PidControl pidControl;
Distance distance;
Direction direction;
Scene scene;
Clock clock;

/* ���[�^�|�[�g */
#define LEFT_MOTOR_P EV3_PORT_C
#define RIGHT_MOTOR_P EV3_PORT_B
#define TAIL_MOTOR_P EV3_PORT_A

#define GYRO_OFFSET  0          /* �W���C���Z���T�I�t�Z�b�g�l(�p���x0[deg/sec]��) */
#define GYRO_OFFSET_LOOKUP (-20)		/* ���b�N�A�b�v�Q�[�g�U���p�W���C���Z���T�I�t�Z�b�g�l */

#define TAIL_ANGLE_DRIVE      3 /* �o�����X���s���̊p�x */
#define TAIL_ANGLE_STAND_UP_1	  97//87  /* ���b�N�A�b�v�U��-���S��~���̊p�x1 */
#define TAIL_ANGLE_STAND_UP_2	  87//75  /* ���b�N�A�b�v�U��-���S��~���̊p�x2 */
#define TAIL_ANGLE_STAND_UP_3     95 /* �K���[�W�U��-���S��~���̊p�x3 */
#define TAIL_ANGLE_STAND_UP_4     92 /* �K���[�W�U��-���S��~���̊p�x4 */

void Linetrace_init(Linetrace* self, int threshold, int lookup_threshold) {
	self->forward = 0; /* �O�i�l������ */
	self->threshold = threshold; /* 臒l�i�[ */
	self->lookup_threshold = lookup_threshold; /* ���b�N�A�b�v�Q�[�g�U���p臒l */

	/* ���s���[�^�G���R�[�_���Z�b�g */
	WheelMotor_reset(LEFT_MOTOR_P);
	WheelMotor_reset(RIGHT_MOTOR_P);

	GyroSensor_reset(); /* �W���C���Z���T���Z�b�g */

	BalanceControl_balance_init(); /* �|���U�qAPI������ */

	PidControl_init(&pidControl, self->threshold); /* Pid���䏉���� */

	Distance_init(&distance); /* �����v������ */

	Direction_init(&direction); /* ���ʌv������ */

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

		time = Clock_get_time(&clock); /* �^�C���擾 */
		if (time < 100) { /* ���̊ԃe�[�������� */
			TailControl_control(TAIL_ANGLE_STAND_UP_1); /* �e�[������ */
		}
		else if (time < 200) { /* ���̊ԃe�[�������� */
			TailControl_control(TAIL_ANGLE_STAND_UP_2); /* �e�[������ */
		}
		else if (time < 300) {
			break;
		}

		distance_num = Distance_calc(&distance); /* ���s�����v�Z */

		scene_num = Scene_get_scene(&scene, distance_num); /* ���s��Ԃ��擾 */

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

		tslp_tsk(4);
	}
	ter_tsk(LINETRACE_TIMER_TASK); /* �^�C�}�[�^�X�N�I�� */

	Clock_reset(&clock); /* �^�C�}�[���Z�b�g */
	act_tsk(LINETRACE_TIMER_TASK); /* �^�C�}�[�^�X�N�J�n */

	uint8_t reflect = 0; /* ���ˌ��l */

	/* ���b�N�A�b�v�Q�[�g���ԑ̂��ʂ�߂���܂őO�i���� */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON)) /* �o�b�N�{�^���ő��s�����I�� */
		{
			break;
		}

		TailControl_control(TAIL_ANGLE_STAND_UP_2); /* �e�[������ */

		reflect = ColorSensor_get_reflect(); /* ���ˌ��l���擾 */

		turn = 50;

		if (reflect > self->lookup_threshold) { /* ����ʂ��}�C�i�X�ɐݒ� */
			turn = -turn;
		}

		time = Clock_get_time(&clock); /* �^�C���擾 */
		if (time > 2700) { /* 2.7�b�㔲���� */
			break;
		}

		ev3_motor_steer(LEFT_MOTOR_P, RIGHT_MOTOR_P, 10, turn); /* ���s�̂�O�i */

		tslp_tsk(4);
	}
	ter_tsk(LINETRACE_TIMER_TASK); /* �^�C�}�[�^�X�N�I�� */

	Linetrace_rotate(-150.0); /* -150�x��] */

	Clock_reset(&clock); /* �^�C�}�[���Z�b�g */
	act_tsk(LINETRACE_TIMER_TASK); /* �^�C�}�[�^�X�N�J�n */
	/* ���b�N�A�b�v�Q�[�g���ԑ̂��ʂ�߂���܂őO�i���� */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON)) /* �o�b�N�{�^���ő��s�����I�� */
		{
			break;
		}

		TailControl_control(TAIL_ANGLE_STAND_UP_2); /* �e�[������ */

		reflect = ColorSensor_get_reflect(); /* ���ˌ��l���擾 */

		turn = 50;

		if (reflect > self->lookup_threshold) { /* ����ʂ��}�C�i�X�ɐݒ� */
			turn = -turn;
		}

		time = Clock_get_time(&clock); /* �^�C���擾 */
		if (time > 5000) { /* 5�b�㔲���� */
			break;
		}

		ev3_motor_steer(LEFT_MOTOR_P, RIGHT_MOTOR_P, 10, turn); /* ���s�̂�O�i */

		tslp_tsk(4);
	}
	ter_tsk(LINETRACE_TIMER_TASK); /* �^�C�}�[�^�X�N�I�� */

	Linetrace_rotate(-160.0); /* -160�x��] */

	Clock_reset(&clock); /* �^�C�}�[���Z�b�g */
	act_tsk(LINETRACE_TIMER_TASK); /* �^�C�}�[�^�X�N�J�n */
	/* ���b�N�A�b�v�Q�[�g���ԑ̂��ʂ�߂���܂őO�i���� */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON)) /* �o�b�N�{�^���ő��s�����I�� */
		{
			break;
		}

		TailControl_control(TAIL_ANGLE_STAND_UP_2); /* �e�[������ */

		reflect = ColorSensor_get_reflect(); /* ���ˌ��l���擾 */

		turn = 50;

		if (reflect > self->lookup_threshold) { /* ����ʂ��}�C�i�X�ɐݒ� */
			turn = -turn;
		}

		time = Clock_get_time(&clock); /* �^�C���擾 */
		if (time > 7000) { /* 7�b�㔲���� */
			break;
		}

		ev3_motor_steer(LEFT_MOTOR_P, RIGHT_MOTOR_P, 10, turn); /* ���s�̂�O�i */

		tslp_tsk(4);
	}
	ter_tsk(LINETRACE_TIMER_TASK); /* �^�C�}�[�^�X�N�I�� */
}

void Linetrace_rotate(float angle) {
	ev3_speaker_play_tone(NOTE_A4, 300);

	float distance_4ms_left = 0.0; /* ���^�C����4ms�Ԃ̑��s���� */
	float distance_4ms_right = 0.0; /* �E�^�C����4ms�Ԃ̑��s���� */
	float direction_num = 0.0; /* ���� */
	/* ��]���� */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON)) /* �o�b�N�{�^���ő��s�����I�� */
		{
			break;
		}

		TailControl_control(TAIL_ANGLE_STAND_UP_2); /* �e�[������ */

		Distance_calc(&distance); /* ���s�����v�Z */
		distance_4ms_left = Distance_get_distance_4ms_left(&distance);
		distance_4ms_right = Distance_get_distance_4ms_right(&distance);

		direction_num = Direction_calc(&direction, distance_4ms_left, distance_4ms_right); /* ���ʂ��擾 */
		char m[20];
		sprintf(m, "dire : %4lf", direction_num);
		ev3_lcd_draw_string(m, 0, 90);
		if (direction_num < angle) {
			break;
		}

		/* �ԑ̂���] */
		ev3_motor_set_power(LEFT_MOTOR_P, -5);
		ev3_motor_set_power(RIGHT_MOTOR_P, 5);

		tslp_tsk(4);
	}

	Direction_reset(&direction); /* ���ʂ����Z�b�g */
}

void Linetrace_garage(Linetrace* self) {
	colorid_t color = 0;

	Clock_reset(&clock); /* �^�C�}�[���Z�b�g */
	act_tsk(LINETRACE_TIMER_TASK); /* �^�C�}�[�^�X�N�J�n */
	int time = 0; /* �^�C�� */
	/* ���E���[�^���ꎞ��~���邱�ƂŎ��̃t�F�[�Y�Ńe�[���������邱�Ƃ��ł��� 
	 * ����Ȃ���ł͌��ɏd�S�������邽�߁A�e�[���������͑���Ȃ��Ȃ�
	 */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON)) /* �o�b�N�{�^���ő��s�����I�� */
		{
			break;
		}

		TailControl_control(TAIL_ANGLE_STAND_UP_2); /* �e�[������ */

		ev3_motor_stop(LEFT_MOTOR_P, false);
		ev3_motor_stop(RIGHT_MOTOR_P, false);

		time = Clock_get_time(&clock); /* �^�C�����擾 */
		if (time > 500) { /* 0.5�b�ニ�[�v�𔲂��� */
			break;
		}

		tslp_tsk(4);
	}
	ter_tsk(LINETRACE_TIMER_TASK); /* �^�C�}�[�^�X�N�I�� */

	/* �̃��C����T�� */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON)) /* �o�b�N�{�^���ő��s�����I�� */
		{
			break;
		}

		TailControl_control(TAIL_ANGLE_STAND_UP_3); /* �e�[������ */

		color = ColorSensor_get_color(); /* �J���[�擾 */
		if (color == 0) {
			ev3_motor_steer(LEFT_MOTOR_P, RIGHT_MOTOR_P, 10, -50);
		}
		else if (color == 1) {
			ev3_motor_steer(LEFT_MOTOR_P, RIGHT_MOTOR_P, 10, 50);
		}
		else if (color == 2) { /* �̃��C���ɓ��B�����烋�[�v�𔲂��� */
			break;
		}

		tslp_tsk(4);
	}

	ter_tsk(LINETRACE_TIMER_TASK); /* �^�C�}�[�^�X�N�I�� */
	ev3_speaker_play_tone(NOTE_A4, 300);

	Clock_reset(&clock); /* �^�C�}�[���Z�b�g */
	act_tsk(LINETRACE_TIMER_TASK); /* �^�C�}�[�^�X�N�J�n */
	/* ���̃t�F�[�Y�̃o�b�N�œ|��Ȃ��悤�ɒx�������� */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON)) /* �o�b�N�{�^���ő��s�����I�� */
		{
			break;
		}

		TailControl_control(TAIL_ANGLE_STAND_UP_3); /* �e�[������ */

		time = Clock_get_time(&clock); /* �^�C���擾 */
		if (time > 500) {
			break;
		}

		ev3_motor_stop(LEFT_MOTOR_P, false);
		ev3_motor_stop(RIGHT_MOTOR_P, false);

		tslp_tsk(4);
	}
	ter_tsk(LINETRACE_TIMER_TASK); /* �^�C�}�[�^�X�N�I�� */

	/* �̃��C������o�� */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON)) /* �o�b�N�{�^���ő��s�����I�� */
		{
			break;
		}

		TailControl_control(TAIL_ANGLE_STAND_UP_3 - 5); /* �e�[������ */

		color = ColorSensor_get_color(); /* �J���[�擾 */
		if (color == 0) {
			ev3_motor_steer(LEFT_MOTOR_P, RIGHT_MOTOR_P, -10, 50);
		}
		else if (color == 2) {
			ev3_motor_steer(LEFT_MOTOR_P, RIGHT_MOTOR_P, -10, -50);
		}
		else if (color == 1) { /* ���̃��C���ɓ��B�����烋�[�v�𔲂��� */
			break;
		}

		tslp_tsk(4);
	}
	ev3_speaker_play_tone(NOTE_F4, 300);

	Clock_reset(&clock); /* �^�C�}�[���Z�b�g */
	act_tsk(LINETRACE_TIMER_TASK); /* �^�C�}�[�^�X�N�J�n */
	time = 0; /* �^�C�� */
	/* ���̃t�F�[�Y�̑O�i�œ|��Ȃ��悤�ɒx�������� */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON)) /* �o�b�N�{�^���ő��s�����I�� */
		{
			break;
		}

		TailControl_control(TAIL_ANGLE_STAND_UP_3); /* �e�[������ */

		time = Clock_get_time(&clock); /* �^�C���擾 */
		if (time > 500) {
			break;
		}

		ev3_motor_stop(LEFT_MOTOR_P, false);
		ev3_motor_stop(RIGHT_MOTOR_P, false);

		tslp_tsk(4);
	}
	ter_tsk(LINETRACE_TIMER_TASK); /* �^�C�}�[�^�X�N�I�� */

	int turn = 0;

	int reflect = 0; /* ���ˌ��l */

	int start_distance = Distance_calc(&distance); /* �K���[�W��ԃX�^�[�g�ʒu���s���� */
	int now_distance = 0; /* ���݂̑��s���� */
	/* �K���[�W��Ԉʒu�܂őO�i */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON)) /* �o�b�N�{�^���ő��s�����I�� */
		{
			break;
		}

		TailControl_control(TAIL_ANGLE_STAND_UP_4); /* �e�[������ */

		now_distance = Distance_calc(&distance); /* ���s�����擾 */

		if ((now_distance - start_distance) > 270) { /* 27cm�O�i�����烋�[�v�𔲂��� */
			break;
		}

		reflect = ColorSensor_get_reflect(); /* ���ˌ��l���擾 */

		turn = 50;

		if (reflect > self->lookup_threshold) { /* ����ʂ��}�C�i�X�ɐݒ� */
			turn = -50;
		}

		ev3_motor_steer(LEFT_MOTOR_P, RIGHT_MOTOR_P, 10, turn); /* ���s�̂�O�i */

		tslp_tsk(4);
	}

	ev3_speaker_play_tone(NOTE_B4, 300);

	/* ��� */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON)) /* �o�b�N�{�^���ő��s�����I�� */
		{
			break;
		}

		TailControl_control(TAIL_ANGLE_STAND_UP_4); /* �e�[������ */

		ev3_motor_stop(LEFT_MOTOR_P, false);
		ev3_motor_stop(RIGHT_MOTOR_P, false);

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
