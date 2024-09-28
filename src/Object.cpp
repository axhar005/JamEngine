#include "../include/Object.h"
#include "../include/Engine.h"

Object::Object(Vector2 _position, Sprite _sprite) : position(_position), sprite(_sprite), frameIndex(0), animationSpeed(0)
{
	texture = &sprite[frameIndex].texture;
	Engine& e = Engine::getInstance();
	e.addObject(*this, true);
}

Object::~Object()
{

}

void Object::step()
{
	// do nothing
}
