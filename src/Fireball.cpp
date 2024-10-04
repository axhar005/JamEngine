#include "../include/Object.h"
#include "../include/Fireball.h"

Fireball::Fireball(Vector2 _position, Sprite _sprite) : Object(_position, _sprite)
{
	this->hitbox.height = 16;
	this->hitbox.width = 16;
	this->hitbox.x = this->position.x;
	this->hitbox.y = this->position.y;
}

Fireball::~Fireball()
{
}

void Fireball::step()
{
	this->hitbox.x = this->position.x;
	this->hitbox.y = this->position.y;
	// do nothing
}
