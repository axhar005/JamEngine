#include "../include/microAddons.h"

float getDistance(Vector2 start, Vector2 end)
{
	Vector2 direction = {end.x - start.x, end.y - start.y};
	return sqrt((direction.x * direction.x) + (direction.y * direction.y));
}

Vector2 getNormalisedVector(Vector2 vector)
{
	Vector2 direction = {vector.x, vector.y};
	float length = getDistance(Vector2{0, 0}, vector);

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

Vector2 getNormalisedDirection(Vector2 start, Vector2 end) {return (getNormalisedVector(Vector2{end.x - start.x, end.y - start.y}));}