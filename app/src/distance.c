#include "ev3api.h"
#include "distance.h"
#include "wheelmotor.h"

/* ¶E[^[|[g */
#define LEFT_MOTOR_P EV3_PORT_C
#define RIGHT_MOTOR_P EV3_PORT_B

#define TIRE_DISMETER 100.0 /* ^CÌ¼a (100mm) */
#define PI 3.14159265358979 /* ~ü¦ */

/*
 * £vú»\bh
 *
 * @param self ©ªÌ|C^
 */
void Distance_init(Distance* self) {
	self->distance = 0.0;
	self->distance_4ms_left = 0.0;
	self->distance_4ms_right = 0.0;

	/* ¶E[^ÌßlÉ»Ýnðãü */
	self->prev_angle_left = WheelMotor_get_angle(LEFT_MOTOR_P);
	self->prev_angle_right = WheelMotor_get_angle(RIGHT_MOTOR_P);
}

/*
 * s£vZ\bh
 *
 * @param self ©ªÌ|C^
 * @return distance s£
 */
float Distance_calc(Distance* self) {
	/* ¶E[^Ìñ]pxðæ¾ */
	float cur_angle_left = WheelMotor_get_angle(LEFT_MOTOR_P); 
	float cur_angle_right = WheelMotor_get_angle(RIGHT_MOTOR_P);

	float distance_4ms = 0.0; /* 4msÌ£ */

	/* ¶E[^Ì4msÔ£ðvZ */
	self->distance_4ms_left = ((PI * TIRE_DISMETER) / 360.0) * (cur_angle_left - self->prev_angle_left);
	self->distance_4ms_right = ((PI * TIRE_DISMETER) / 360.0) * (cur_angle_right - self->prev_angle_right);
	distance_4ms = ((self->distance_4ms_left + self->distance_4ms_right) / 2.0); /* 4msÌ£ðvZ */
	self->distance += distance_4ms;

	/* [^Ìñ]paßlðXV */
	self->prev_angle_left = cur_angle_left;
	self->prev_angle_right = cur_angle_right;

	return self->distance;
}

/*
 * ¶^CÌ4msÔÌs£æ¾\bh
 *
 * @param self ©ªÌ|C^
 * @return distance_4ms_left ¶^CÌ4msÔÌs£
 */
float Distance_get_distance_4ms_left(Distance* self) {
	return self->distance_4ms_left;
}

/*
 * E^CÌ4msÔÌs£æ¾\bh
 *
 * @param self ©ªÌ|C^
 * @return distance_4ms_right E^CÌ4msÔÌs£
 */
float Distance_get_distance_4ms_right(Distance* self){
	return self->distance_4ms_right;
}
