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

PidControl pidControl;
Distance distance;
Scene scene;

/* ���[�^�|�[�g */
#define LEFT_MOTOR_P EV3_PORT_C
#define RIGHT_MOTOR_P EV3_PORT_B
#define TAIL_MOTOR_P EV3_PORT_A

#define GYRO_OFFSET  0          /* �W���C���Z���T�I�t�Z�b�g�l(�p���x0[deg/sec]��) */

#define TAIL_ANGLE_DRIVE      3 /* �o�����X���s���̊p�x */
#define FORWARD 40 /* �O�i�l */

void Linetrace_init(Linetrace* self, int threshold) {
	self->forward = 0; /* �O�i�l������ */

	/* ���s���[�^�G���R�[�_���Z�b�g */
	WheelMotor_reset(LEFT_MOTOR_P);
	WheelMotor_reset(RIGHT_MOTOR_P);

	GyroSensor_reset(); /* �W���C���Z���T���Z�b�g */

	BalanceControl_balance_init(); /* �|���U�qAPI������ */

	PidControl_init(&pidControl, threshold); /* Pid���䏉���� */

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

	int scene_num = -1; /* ���s��� */

	/* 4msec�����ő��s */
	while (1) {
		if (ev3_button_is_pressed(BACK_BUTTON) || TouchSensor_is_pressed()) /* �o�b�N�{�^���ő��s�����I�� */
		{
			break;
		}

		TailControl_control(TAIL_ANGLE_DRIVE); /* �e�[������ */

		Distance_update(&distance); /* ���Ȉʒu������X�V */

		distance_num = Distance_get_distance(&distance); /* ���s�����擾 */

		scene_num = Scene_get_scene(&scene, distance_num); /* ���s��Ԃ��擾 */

		RunningStyle_switch(scene_num,self,&pidControl); /* ���@�؂�ւ� */

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