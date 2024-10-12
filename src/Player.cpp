#include "../include/Player.h"
#include "../include/Engine.h"

Player::Player(Vector2 _position, Sprite _sprite, bool _visible) : Object(_position, _sprite, _visible), showHitbox(false)
{
	animationSpeed = 1;
}

Player::Player(Vector2 _position, Sprite _sprite, bool _visible, int _layerLV): Object(_position, _sprite, _visible, _layerLV), showHitbox(false)
{
	animationSpeed = 1;
}

Player::~Player()
{

}

void Player::step()
{
	static int t = 0;
	if (t < 60)
		rotation++;
	else 
		t = 0;
	t++;
}

void Player::draw()
{
	Engine& e = Engine::getInstance();
	if (CheckCollisionEllipseRecs(hitbox.box, e.objectList[2]->hitbox.box))
	{
		DrawRectangleRec(this->hitbox.box, {255, 255, 0, 200});
		Ellipse el = getEllipseFromRec(this->hitbox.box);
		DrawEllipse((int)el.center.x, (int)el.center.y, el.radiusX, el.radiusY, {0, 255, 128, 200});
		Vector2 vec; 
		GetEllipseCollision(vec, hitbox.box, e.objectList[2]->hitbox.box);
		DrawCircle((int)vec.x, (int)vec.y, 1, {0, 0, 0, 255});
	}
}