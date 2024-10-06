#include "../include/Fireball.h"
#include "../include/Engine.h"

//testpush

Fireball::Fireball(Vector2 _position, Sprite _sprite, bool _visible) : Object(_position, _sprite, _visible)
{
	hitbox.box.height = 16;
	hitbox.box.width = 16;
	hitbox.box.x = position.x + hitbox.offset.x;
	hitbox.box.y = position.y + hitbox.offset.y;
}

Fireball::Fireball(Vector2 _position, Sprite _sprite, bool _visible, int _layerLV) : Object(_position, _sprite, _visible, _layerLV)
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

void Fireball::draw()
{

}
