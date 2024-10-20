#include "../../include/microbial/microSetup.h"

Nutrient::Nutrient(Vector2 _position, Sprite _sprite, PetriDish* _petriDish, float _mass, bool addToPetriDish) :
	Object(_position, _sprite, true)
{
	this->petriDish = _petriDish;
	if (addToPetriDish)
		this->petriDish->addNutrient(this);
	this->mass = _mass;

	if (this->mass <= 0)
		this->setRandomMass();

	this->species = "Nutrient";

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
	this->hitbox.box.height = this->getSize();
	this->hitbox.box.width = this->getSize();
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
	this->mass += amount;
	if (this->mass > NUTRIENT_MAX_MASS)
	{
		this->mass = NUTRIENT_MAX_MASS;
	}
}

void Nutrient::shrink(float amount)
{
	this->mass -= amount;
	if (this->mass < NUTRIENT_MIN_MASS)
	{
		this->die();
	}
}


void Nutrient::setRandomMass()
{
	this->mass = GetRandomValue(NUTRIENT_MIN_MASS, NUTRIENT_MAX_MASS);
}

void Nutrient::die()
{
	/*
	this->petriDish->removeNutrient(this);
	this->petriDish->spawnNutrient(this->sprite, 1);
	delete this;
	*/

	// tmp fix for object deletion bug
	this->position = this->petriDish->getRandomPos();
	this->refreshPos();

	this->setRandomMass();
	this->refreshSize();
}

bool Nutrient::overlapsOther(Nutrient* other)
{
	if (CheckCollisionRecs(this->hitbox.box, other->hitbox.box))
		return true;
	return false;
}

bool Nutrient::isOnEdge()
{
	// check if nutrient is near the edge of the petriDish, to avoid faceplanting into the wall
	if (getDistance(this->position, Vector2{0, 0}) > this->petriDish->getRadius() - this->getSize())
		return true;
	return false;
}

bool Nutrient::canBeConsumedBy(Nutrient* target) {return target->canConsume(this);}
bool Nutrient::canConsume(Nutrient* target) {(void)target; return false;}

float				Nutrient::getMass()			{return this->mass;}
float				Nutrient::getSize()			{return sqrtf(this->mass);}
Vector2&		Nutrient::getPosition()	{return this->position;}
std::string	Nutrient::getSpecies()	{return this->species;}
PetriDish*	Nutrient::getPetriDish(){return this->petriDish;}
float				Nutrient::getDistanceTo(Nutrient* target) {return getDistance(this->position, target->getPosition());}
float				Nutrient::getTaxiCabDistanceTo(Nutrient* target) {return getTaxiCabDistance(this->position, target->getPosition());}

