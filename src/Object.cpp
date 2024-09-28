#include "../include/Object.h"
#include "../include/Engine.h"

Object::Object(Vector2 _position, Sprite _sprite) : sprite(_sprite), position(_position), frameIndex(0), animationSpeed(0)
{
	if (!sprite.empty()){
		texture = &sprite[frameIndex].texture;
		hitbox.box.height = texture->height;
		hitbox.box.width = texture->width;
	}
}

Object::~Object()
{

}

void Object::updateHitbox()
{

}

void Object::step()
{
	// do nothing
}
