#include "../include/Object.h"
#include "../include/Fireball.h"

Fireball::Fireball(Vector2 _position, Sprite _sprite) : Object(_position, _sprite)
{
	std::cout << "test" << std::endl;
}

Fireball::~Fireball()
{
	std::cout << "test end" << std::endl;
}

void Fireball::step()
{
	// do nothing
}
