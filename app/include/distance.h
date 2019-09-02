#ifndef _DISTANCE_H_
#define _DISTANCE_H_

typedef struct {
	float distance; /* 走行距離 */
	float distance_4ms_left; /* 左タイヤの4ms間の距離 */
	float distance_4ms_right; /* 右タイヤの4ms間の距離 */

	float prev_angle_left; /* 前回の左モータ回転角度 */
	float prev_angle_right; /* 前回の右モータ回転角度 */
}Distance;
void Distance_init(Distance* self);
void Distance_update(Distance* self);
float Distance_get_distance(Distance* self);

#endif