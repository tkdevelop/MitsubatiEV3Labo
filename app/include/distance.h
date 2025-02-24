#ifndef _DISTANCE_H_
#define _DISTANCE_H_

typedef struct {
	float distance; /* s£ */
	float distance_4ms_left; /* ¶^CÌ4msÔÌ£ */
	float distance_4ms_right; /* E^CÌ4msÔÌ£ */

	float prev_angle_left; /* OñÌ¶[^ñ]px */
	float prev_angle_right; /* OñÌE[^ñ]px */
}Distance;
void Distance_init(Distance* self);
float Distance_calc(Distance* self);
float Distance_get_distance_4ms_left(Distance* self);
float Distance_get_distance_4ms_right(Distance* self);

#endif