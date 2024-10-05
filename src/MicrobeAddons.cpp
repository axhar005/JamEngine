#include "../include/Microbe.h"
#include <cmath>

Vector2 getNormalisedDirection(Vector2 start, Vector2 end)
{
	Vector2 direction = {end.x - start.x, end.y - start.y};
	float length = sqrt((direction.x * direction.x) + (direction.y * direction.y));

	if (length != 0)
	{
		direction.x /= length;
		direction.y /= length;
	}
	else
	{
		direction.x = 0;
		direction.y = 0;
	}

	return direction;
}