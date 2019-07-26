#ifndef _DISTANCE_H_
#define _DISTANCE_H_

typedef struct {
	float distance; /* 走行距離 */

	float preAngleLeft; /* 前回の左モータ回転角度 */
	float preAngleRight; /* 前回の右モータ回転角度 */
}Distance;
void Distance_init(Distance* self);
void Distance_update(Distance* self);
void Distance_get_distance();

#endif