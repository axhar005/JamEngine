#include "../include/Object.h"
#include "../include/Fireball.h"

Fireball::Fireball(Vector2 _position, Sprite _sprite) : Object(_position, _sprite)
{
}

Fireball::~Fireball()
{
}

void Fireball::step()
{
	// do nothing
	std::cout << this->position.x << std::endl;
	this->position.x++;
	if (this->position.x > GetScreenWidth())
		this->position.x = 0;
}
