#include "../include/Object.h"
#include "../include/Engine.h"

Object::Object(Vector2 _position, Sprite _sprite, bool _visible) : visible(_visible), sprite(_sprite), position(_position), frameIndex(0), animationSpeed(0), rotation(0), layer(0)
{
	if (!sprite.empty()){
		texture = &sprite[frameIndex].texture;
		hitbox.box.height = texture->height;
		hitbox.box.width = texture->width;
		hitbox.offset = {0, 0};
	}
	Engine& e = Engine::getInstance();
	e.addObject(this);
	if (visible)
		e.addObjectToRender(this);
}

Object::Object(Vector2 _position, bool _visible) :  visible(_visible), position(_position), frameIndex(0), animationSpeed(0), rotation(0), layer(0)
{
	hitbox.offset = {0, 0};
	hitbox.box = {0, 0, 0, 0};
	Engine& e = Engine::getInstance();
	e.addObject(this);
	if (visible)
		e.addObjectToRender(this);
}

Object::Object(Vector2 _position, Sprite _sprite, bool _visible, int _layerLV) :  visible(_visible), sprite(_sprite), position(_position), frameIndex(0), animationSpeed(0), rotation(0), layer(_layerLV)
{
	if (!sprite.empty()){
		texture = &sprite[frameIndex].texture;
		hitbox.box.height = texture->height;
		hitbox.box.width = texture->width;
		hitbox.offset = {0, 0};
	}
	Engine& e = Engine::getInstance();
	e.addObject(this);
	if (visible)
		e.addObjectToRender(this);
}

void Object::setName(const char* _name) {
	if (_name)
		this->name = _name;
}

const std::string& Object::getName(void) {
	return this->name;
}

Object::~Object()
{
	Engine::getInstance().removeObject(this);
}

void Object::update(){
	hitbox.box.x = position.x + hitbox.offset.x;
	hitbox.box.y = position.y + hitbox.offset.x;
	if (animationSpeed != 0)
	{
		size_t next = frameIndex++;
		if (next < 0)
			next = sprite.size() - 1;
		else if (next > sprite.size() - 1)
			next = 0;
		texture = &sprite[next].texture;
	}
}

void Object::step()
{
	
}

void Object::draw()
{

}

int Object::getLayer(){
	return layer;
}

void Object::setLayer(int _layerLV){
	layer = _layerLV;
	Engine::getInstance().sortLayer();
}

bool Object::getVisible(){
	return visible;
}

void Object::setVisible(bool _visible){
	if (_visible == true && this->visible != true)
	{
		Engine::getInstance().addObjectToRender(this);
	}
	else if (_visible == false && this->visible == true)
	{
		Engine::getInstance().removeObjectFromRenderByID(this->id);
	}
}

void Object::setSprite(std::string name)
{
	rotation = 0;
	frameIndex = 0;
	sprite = Engine::getInstance().getSprite(name);
}