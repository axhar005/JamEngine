#include "../include/Object.h"
#include "../include/Engine.h"

Object::Object(Vector2 _position, Sprite _sprite) : sprite(_sprite), position(_position), frameIndex(0), animationSpeed(0), layer(0)
{
	if (!sprite.empty()){
		texture = &sprite[frameIndex].texture;
		hitbox.height = texture->height;
		hitbox.width = texture->width;
	}
}

Object::Object(Vector2 _position, Sprite _sprite, int layerLV) : sprite(_sprite), position(_position), frameIndex(0), animationSpeed(0), layer(layerLV) {
	if (!sprite.empty()){
		texture = &sprite[frameIndex].texture;
		hitbox.height = texture->height;
		hitbox.width = texture->width;
	}
}

Object::~Object()
{

}

void Object::update(){
	hitbox.x = this->position.x;
	hitbox.y = this->position.y;
}

void Object::step()
{
	// do nothing
}
