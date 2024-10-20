#ifndef HITBOX_H
# define HITBOX_H
	#include <raylib.h>
	struct Ellipse
	{
		Vector2 center;
		float radiusX;
		float radiusY;
	};

	#define SHOW_HITBOX true

	Ellipse getEllipseFromRec(Rectangle rec);
	bool CheckCollisionEllipseRecs(Rectangle rec1, Rectangle rec2);
	bool GetEllipseCollision(Vector2& pos, Rectangle rec1, Rectangle rec2);
#endif