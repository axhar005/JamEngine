#ifndef HITBOX_H
# define HITBOX_H
	#include "../include/engineSetup.h"
	struct Ellipse
	{
		Vector2 center;
		float radiusX;
		float radiusY;
	};

	Ellipse getEllipseFromRec(Rectangle rec);
	bool CheckCollisionEllipseRecs(Rectangle rec1, Rectangle rec2);
	bool GetEllipseCollision(Vector2& pos, Rectangle rec1, Rectangle rec2);
#endif