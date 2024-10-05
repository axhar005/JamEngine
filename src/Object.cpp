#include "../include/Object.h"
#include "../include/Engine.h"

Object::Object(Vector2 _position, Sprite _sprite) : sprite(_sprite), position(_position), frameIndex(0), animationSpeed(0), layer(0)
{
	if (!sprite.empty()){
		texture = &sprite[frameIndex].texture;
		hitbox.box.height = texture->height;
		hitbox.box.width = texture->width;
		hitbox.offset = {0, 0};
	}
}

Object::Object(Vector2 _position) : position(_position), frameIndex(0), animationSpeed(0), layer(0) {

}

Object::Object(Vector2 _position, Sprite _sprite, int _layerLV) : sprite(_sprite), position(_position), frameIndex(0), animationSpeed(0), layer(_layerLV) {
	if (!sprite.empty()){
		texture = &sprite[frameIndex].texture;
		hitbox.box.height = texture->height;
		hitbox.box.width = texture->width;
	}
}

Object::~Object()
{
	Engine::getInstance().removeObjectByID(this->id);
}

void Object::update(){
	hitbox.box.x = position.x + hitbox.offset.x;
	hitbox.box.y = position.y + hitbox.offset.x;
}

void Object::step()
{
	// do nothing
}

void Object::draw()
{
	
}
