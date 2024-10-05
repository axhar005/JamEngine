#include "../include/Microbe.h"
#include <raylib.h>

Microbe::Microbe(Vector2 _position, Sprite _sprite, std::string _species, bool _isPlayer) :
	Nutrient(_position, _sprite, MICROBE_START_SIZE)
{
	this->refreshSpeed(); //	makes speed invertly proportional to its size
	this->refreshSize(); //		sets hitbox size to size
	this->refreshPos(); //		sets hitbox position to position ( clamped to petriDish )

	this->species = _species;
	this->isPlayer = _isPlayer;
}

Microbe::~Microbe()
{
}

void Microbe::step()
{
	this->shrink(MICROBE_STARVE_RATE); // lose size each tick

	this->refreshPos();
	this->refreshSize();
	this->refreshSpeed();

	if (this->isPlayer)
	{
		// player controls here
	}
	else
		this->wander();
}


void Microbe::refreshSpeed()
{
	// speed is inversely proportional to size, and linearly distributed between min and max speed

	float speed_range = MICROBE_MAX_SPEED - MICROBE_MIN_SPEED;
	float size_range = MICROBE_MAX_SIZE - MICROBE_MIN_SIZE;

	float norm_size = (this->size - MICROBE_MIN_SIZE) / size_range;

	this->speed = MICROBE_MIN_SPEED + ((1 - norm_size) * speed_range);
}

void Microbe::grow(int amount)
{
	this->size += amount;
	if (this->size > MICROBE_MAX_SIZE)
	{
		this->size = MICROBE_MAX_SIZE;
		this->refreshSpeed();
	}
}

void Microbe::shrink(int amount)
{
	this->size -= amount;
	if (this->size < MICROBE_MIN_SIZE)
	{
		this->starve();
	}
}

void Microbe::divide()
{
	if (this->size > MICROBE_MIN_DIV_SIZE)
	{
		this->size /= 2;
		this->refreshSpeed();

		Microbe* newMicrobe = new Microbe(this->position, this->sprite, this->species, false);
		newMicrobe->size = this->size;
		newMicrobe->refreshSpeed();

		// add newMicrobe to PetriDish
	}
}

void Microbe::starve()
{
	if (this->isPlayer)
	{
		// tag to Microbe of same species
		// game over if none found
	}

	// NOTE : use nutrient sprite instead
	Nutrient* nutrient = new Nutrient(this->position, this->sprite, this->size);

	// add nutrient to PetriDish

	this->die();
}

void Microbe::die()
{
	// remove this from PetriDish
}

Microbe* Microbe::findClosestPredator()
{
	// find closest predator
	// return pointer to it
	return nullptr;
}

Microbe* Microbe::findClosestPrey()
{
	// find closest prey
	// return pointer to it
	return nullptr;
}


Nutrient* Microbe::findClosestNutrient()
{
	// find closest nutrient
	// return pointer to it
	return nullptr;
}


void Microbe::getNewWanderGoal()
{
	// create a random goal within a certain distance from this->position, and set it as wanderGoal
}

void Microbe::move(Vector2 direction)
{
	// NOTE : assumes direction is normalized
	this->position.x += direction.x * this->speed;
	this->position.y += direction.y * this->speed;
}

void Microbe::moveTowards(Vector2 target)
{
	Vector2 direction = getNormalisedDirection(this->position, target);
	this->move(direction);
}

void Microbe::moveAwayFrom(Vector2 target)
{
	Vector2 direction = getNormalisedDirection(target, this->position);
	this->move(direction);
}

void Microbe::wander()
{
	// if found predators of other species, move away from them
	// if found prey of other species, move towards them
	// if found nutrients, move towards them
	// if found same species, move away from them
	// if none found, use wander goal
	// if goal reach, set new goal
}

void Microbe::devour(Microbe* target)
{
	if (this->canDevour(target))
	{
		this->grow(target->getSize() * MICROBE_DIGESTION_FACTOR);
		target->die();
	}
}


void Microbe::graze(Nutrient* target)
{
	if (this->canGraze(target))
	{
		this->grow(target->getSize());
		target->die();
	}
}


bool Microbe::overlapsOther(Microbe* target)
{
	// check if this->hitbox overlaps with target->hitbox
	return false;
}

bool Microbe::overlapsNutrient(Nutrient* target)
{
	// check if this->hitbox overlaps with target->hitbox
	return false;
}

bool Microbe::canGraze(Nutrient* target)
{
	if (this->size * MICROBE_CANIBALISM_FACTOR < target->getSize()) {return false;}
	return true;
}

bool Microbe::canDevour(Microbe* target)
{
	if (this->isSameSpecies(target)) {return false;}
	if (this->size * MICROBE_CANIBALISM_FACTOR < target->size ) {return false;}
	return true;
}

bool Microbe::canBeDevouredBy(Microbe* target) {return target->canDevour(this);}
bool Microbe::isSameSpecies(Microbe* target) {return this->species == target->species;}

bool Microbe::hasReachedWanderGoal()
{
	if (this->position.x > this->wanderGoal.x + MICROBE_GOAL_RADIUS ||
		this->position.x < this->wanderGoal.x - MICROBE_GOAL_RADIUS)
		return false;

	if (this->position.y > this->wanderGoal.y + MICROBE_GOAL_RADIUS ||
		this->position.y < this->wanderGoal.y - MICROBE_GOAL_RADIUS)
		return false;

	return true;
}

int Microbe::getSpeed() {return this->speed;}
std::string Microbe::getSpecies() {return this->species;}
