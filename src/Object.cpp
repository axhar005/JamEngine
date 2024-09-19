#include "../include/Object.h"

Object::Object(Vector2 _position, Sprite _sprite) : position(_position), sprite(_sprite), frameIndex(0), animationSpeed(0)
{
	texture = &sprite[frameIndex].texture;
}

Object::~Object()
{

}

void Object::step()
{
	// do nothing
}
