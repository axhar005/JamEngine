#include "../include/Object.h"
#include "../include/Fireball.h"

//testpush

Fireball::Fireball(Vector2 _position, Sprite _sprite) : Object(_position, _sprite)
{
	hitbox.box.height = 16;
	hitbox.box.width = 16;
	hitbox.box.x = position.x + hitbox.offset.x;
	hitbox.box.y = position.y + hitbox.offset.y;
}

Fireball::~Fireball()
{
}

void Fireball::step()
{
	hitbox.box.x = position.x + hitbox.offset.x;
	hitbox.box.y = position.y + hitbox.offset.y;
	// do nothing
}
