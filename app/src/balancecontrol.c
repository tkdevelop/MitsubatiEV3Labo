#include "ev3api.h"
#include "balancer.h"
#include "balancecontrol.h"

/*
 * �o�b�N���b�V���L�����Z�����\�b�h
 *
 * @param lpwm �����[�^PWM�l(�O��̏o�͒l)
 * @param rpwm �E���[�^PWM�l(�O��̏o�͒l)
 * @param lenc �����[�^�G���R�[�_�l
 * @param renc �E���[�^�G���R�[�_�l
 */
void BalanceControl_backlash_cancel(signed char lpwm, signed char rpwm, int32_t *lenc, int32_t *renc) {
	const int BACKLASHHALF = 4;   // �o�b�N���b�V���̔���[deg]

	if (lpwm < 0) *lenc += BACKLASHHALF;
	else if (lpwm > 0) *lenc -= BACKLASHHALF;

	if (rpwm < 0) *renc += BACKLASHHALF;
	else if (rpwm > 0) *renc -= BACKLASHHALF;
}

/*
 * �o�����X�R���g���[�����������\�b�h
 *
 * @param self �����̃|�C���^
 */
void BalanceControl_balance_init() {
	balance_init(); /* �|���U�qAPI������ */
}

/*
 * �o�����X�R���g���[�����\�b�h
 *
 * @param forward �O�i�l
 * @param turn ���񖽗�
 * @param gyro �W���C���Z���T�l
 * @param GYRO_OFFSET �W���C���Z���T�I�t�Z�b�g�l
 * @param motor_ang_l �����[�^�G���R�[�_�l
 * @param motor_ang_r �E���[�^�G���R�[�_�l
 * @param volt �o�b�e���d���l
 * @param pwm_L �����[�^PWM�o�͒l
 * @param pwm_R �E���[�^PWM�o�͒l
 */
void BalanceControl_balance_control(float forward, float turn, float gyro,
float GYRO_OFFSET, float motor_ang_l, float motor_ang_r,
float volt, signed char *pwm_L, signed char *pwm_R) {
	balance_control(
		forward,
		turn,
		gyro,
		GYRO_OFFSET,
		motor_ang_l,
		motor_ang_r,
		volt,
		pwm_L,
		pwm_R); /* ���E���[�^�o�͒l�𓾂� */
}