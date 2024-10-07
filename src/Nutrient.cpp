#include "../include/Nutrient.h"
#include "../include/PetriDish.h"

Nutrient::Nutrient(Vector2 _position, Sprite _sprite, PetriDish* _petriDish, float _size, bool addToPetriDish) :
	Object(_position, _sprite, true)
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
	this->refreshPos();

	// add overlapping nutrient fusion logic ??
}

void Nutrient::refreshSize()
{
	this->hitbox.box.height = this->size;
	this->hitbox.box.width = this->size;
}

void Nutrient::refreshPos()
{
	//this->clampPos();

	this->hitbox.box.x = this->position.x; // + hitbox.offset.x;
	this->hitbox.box.y = this->position.y; // + hitbox.offset.y;
}

void Nutrient::clampPos()
{

	if ( getDistance(this->position, Vector2{0, 0}) > this->petriDish->getRadius())
	{
		Vector2 newPosDir = getNormalisedDirection(Vector2{0, 0}, this->position);
		this->position.x = newPosDir.x * this->petriDish->getRadius();
		this->position.y = newPosDir.y * this->petriDish->getRadius();
	}
}

void Nutrient::grow(float amount)
{
	this->size += amount;
	if (this->size > NUTRIENT_MAX_SIZE)
	{
		this->size = NUTRIENT_MAX_SIZE;
	}
}

void Nutrient::shrink(float amount)
{
	this->size -= amount;
	if (this->size < NUTRIENT_MIN_SIZE)
	{
		this->die();
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
	//this->petriDish->spawnNutrient(this->sprite, 1);
	//delete this;

	// tmp fix for object deletion bug
	this->position = this->petriDish->getRandomPos();
	this->refreshPos();

	this->setRandomSize();
	this->refreshSize();
}

float Nutrient::getSize() {return this->size;}
PetriDish* Nutrient::getPetriDish() {return this->petriDish;}

bool Nutrient::overlapsOther(Nutrient* other)
{
	if (CheckCollisionRecs(this->hitbox.box, other->hitbox.box))
		return true;
	return false;
}

bool Nutrient::isOnEdge()
{
	// check if nutrient is near the edge of the petriDish, to avoid faceplanting into the wall
	// TODO : implement me
	return true;
}