#ifndef _DIRECTION_H_
#define _DIRECTION_H_

#include "distance.h"

typedef struct {
	Distance* distance;

	float direction; /* åªç›ÇÃï˚à  */
}Direction;
void Direction_init(Direction* self,Distance* distance);
void Direction_update(Direction* self);
float Direction_get_direction(Direction* self);

#endif