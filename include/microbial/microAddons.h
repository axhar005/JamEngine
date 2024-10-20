#ifndef MICROADDONS_H
# define MICROADDONS_H
	#include <raylib.h>
	#include <cmath>

	float getDistance(Vector2 start, Vector2 end);
	float getTaxiCabDistance(Vector2 start, Vector2 end);
	Vector2 getNormalisedDirection(Vector2 start, Vector2 end);
	Vector2 getNormalisedVector(Vector2 vector);

#endif