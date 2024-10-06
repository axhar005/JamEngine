#include "../include/Player.h"

Player::Player(Vector2 _position) : Object(_position), showHitbox(false)
{

}

Player::Player(Vector2 _position, Sprite _sprite) : Object(_position, _sprite), showHitbox(false)
{

}

Player::Player(Vector2 _position, Sprite _sprite, int _layerLV): Object(_position, _sprite, _layerLV), showHitbox(false)
{

}

Player::~Player()
{

}

void Player::step()
{

}

void Player::draw()
{
	if (showHitbox == true)
	{
		DrawRectangleRec(this->hitbox.box, {255, 255, 0, 200});
	}
}