#include "../include/Nutrient.h"
#include "../include/PetriDish.h"

Nutrient::Nutrient(Vector2 _position, Sprite _sprite, PetriDish* _petriDish, int _size, bool addToPetriDish) :
	Object(_position, _sprite)
{
	this->petriDish = _petriDish;
	if (addToPetriDish)
		this->petriDish->addNutrient(this);
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
	this->petriDish->removeNutrient(this);
	delete this;
}

int Nutrient::getSize() {return this->size;}
PetriDish* Nutrient::getPetriDish() {return this->petriDish;}