#ifndef _BALANCECONTROL_H_
#define _BALANCECONTROL_H_

void BalanceControl_backlash_cancel(signed char lpwm, signed char rpwm, int32_t *lenc, int32_t *renc);
void BalanceControl_balance_init();
void BalanceControl_balance_control(float forward, float turn, float gyro,
float GYRO_OFFSET, float motor_ang_l, float motor_ang_r,
float volt, signed char* pwm_L, signed char* pwm_R);

#endif