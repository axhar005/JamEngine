#include "../include/hitbox.h"

// Function to generate an ellipse from a rectangle
Ellipse getEllipseFromRec(Rectangle rec) {
	Ellipse ellipse;
	ellipse.center.x = rec.x + rec.width / 2;
	ellipse.center.y = rec.y + rec.height / 2;
	ellipse.radiusX = rec.width / 2;
	ellipse.radiusY = rec.height / 2;
	return ellipse;
}

// Function to test collision between two rectangles as ellipses
bool CheckCollisionEllipseRecs(Rectangle rec1, Rectangle rec2) {
	// Convert rectangles to ellipses
	Ellipse e1 = getEllipseFromRec(rec1);
	Ellipse e2 = getEllipseFromRec(rec2);

	// Calculate the distance between the centers of the ellipses
	float dx = e2.center.x - e1.center.x;
	float dy = e2.center.y - e1.center.y;

	// Compare distances based on the ellipses' radii (normalized)
	float distanceX = (dx * dx) / ((e1.radiusX + e2.radiusX) * (e1.radiusX + e2.radiusX));
	float distanceY = (dy * dy) / ((e1.radiusY + e2.radiusY) * (e1.radiusY + e2.radiusY));

	// If the sum of the normalized distances is less than or equal to 1, there is a collision
	return (distanceX + distanceY) <= 1.0f;
}

// Function to get the collision point between two rectangles as ellipses (or NULL if no collision)
bool GetEllipseCollision(Vector2& pos, Rectangle rec1, Rectangle rec2) {
	if (!CheckCollisionEllipseRecs(rec1, rec2)) {
		return false; // No collision
	}

	// Convert rectangles to ellipses
	Ellipse e1 = getEllipseFromRec(rec1);
	Ellipse e2 = getEllipseFromRec(rec2);

	// Simplified: return the midpoint between the two ellipse centers
	pos.x = (e1.center.x + e2.center.x) / 2;
	pos.y = (e1.center.y + e2.center.y) / 2;

	return true;
}
