#ifndef MICROADDONS_H
# define MICROADDONS_H
	#include <raylib.h>
	#include <cmath>

	#define root2 1.41421356237f
	#define root3 1.73205080757f
	#define root5 2.2360679775f

	float getDistance(Vector2 start, Vector2 end);
	float getTaxiCabDistance(Vector2 start, Vector2 end);
	Vector2 getNormalisedDirection(Vector2 start, Vector2 end);
	Vector2 getNormalisedVector(Vector2 vector);

#endif