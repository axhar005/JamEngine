#include "../include/Nutrient.h"
#include "../include/Engine.h"

Nutrient::Nutrient(Vector2 _position, Sprite _sprite, int _size) :
	Object(_position, _sprite)
{
	this->size = _size;

	if (this->size <= 0)
		this->setRandomSize();

	this->refreshSize();
	this->refreshPos();
}

Nutrient::~Nutrient()
{
}

void Nutrient::step()
{
	this->grow(NUTRIENT_GROWTH_RATE); // gain size each tick

	this->refreshSize();
	//this->refreshPos();
}

void Nutrient::refreshSize()
{
	hitbox.box.height = this->size;
	hitbox.box.width = this->size;
}

void Nutrient::refreshPos()
{
	// clamp position to within petriDish

	hitbox.box.x = position.x; // + hitbox.offset.x;
	hitbox.box.y = position.y; // + hitbox.offset.y;
}

void Nutrient::grow(int amount)
{
	this->size += amount;
	if (this->size > NUTRIENT_MAX_SIZE)
	{
		this->size = NUTRIENT_MAX_SIZE;
	}
}

void Nutrient::setRandomSize()
{
	this->size = GetRandomValue(NUTRIENT_MIN_SIZE, NUTRIENT_MAX_SIZE);

	hitbox.box.height = this->size;
	hitbox.box.width = this->size;
}

void Nutrient::die()
{
	// remove this from PetriDish
}

int Nutrient::getSize() {return this->size;}