#ifndef _DISTANCE_H_
#define _DISTANCE_H_

typedef struct {
	float distance; /* s£ */
	float distance4msL; /* ¶^CÌ4msÔÌ£ */
	float distance4msR; /* E^CÌ4msÔÌ£ */

	float preAngleLeft; /* OñÌ¶[^ñ]px */
	float preAngleRight; /* OñÌE[^ñ]px */
}Distance;
void Distance_init(Distance* self);
void Distance_update(Distance* self);
float Distance_get_distance(Distance* self);
float Distance_get_distance_4ms_right(Distance* self);
float Distance_get_distance_4ms_left(Distance* self);

#endif