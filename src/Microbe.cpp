#include "../include/Object.h"
#include "../include/Microbe.h"

//testpush

Microbe::Microbe(Vector2 _position, Sprite _sprite, std::string _species, bool _isPlayer) :
	Object(_position, _sprite)
{
	this->size = MICROBE_START_SIZE;
	this->refreshSpeed(); // makes speed invertly proportional to size

	hitbox.box.height = this->size;
	hitbox.box.width = this->size;

	hitbox.box.x = position.x; // + hitbox.offset.x;
	hitbox.box.y = position.y; // + hitbox.offset.y;

	this->species = _species;
	this->isPlayer = _isPlayer;
}

Microbe::~Microbe()
{
}

void Microbe::step()
{
	hitbox.box.height = this->size;
	hitbox.box.width = this->size;

	hitbox.box.x = position.x; // + hitbox.offset.x;
	hitbox.box.y = position.y; // + hitbox.offset.y;

	this->shrink(MICROBE_STARVE_RATE);

	if (this->isPlayer)
	{
		// player controls here
	}
	else
	{
		// Bot logic here
	}
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

		// add newMicrobe to object list
	}
}

void Microbe::refreshSpeed()
{
	// speed is inversely proportional to size, and linearly distributed between min and max speed

	float speed_range = MICROBE_MAX_SPEED - MICROBE_MIN_SPEED;
	float size_range = MICROBE_MAX_SIZE - MICROBE_MIN_SIZE;

	float norm_size = (this->size - MICROBE_MIN_SIZE) / size_range;

	this->speed = MICROBE_MIN_SPEED + ((1 - norm_size) * speed_range);

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

/*
Food* Microbe::findClosestFood()
{
	// find closest food
	// return pointer to it
	return nullptr;
}
*/

void Microbe::getNewWanderGoal()
{
	// create a random goal within a certain distance from this->position
}

void Microbe::move(Vector2 direction)
{
	// assumes direction is normalized. if not, normalize it here
	this->position.x += direction.x * this->speed;
	this->position.y += direction.y * this->speed;
}

void Microbe::moveTowards(Vector2 target)
{
	// create a normalized vector from this->position to target
	// this->move(vector)
}

void Microbe::moveAwayFrom(Vector2 target)
{
	// create a normalized vector from target to this->position
	// this->move(vector)
}

void Microbe::wander()
{
	// look for predators, prey, food
	// if none found, use wander goal
	// if goal reach, set new goal

}

void Microbe::devour(Microbe* target)
{
	if (this->canDevour(target))
	{
		this->grow(target->size * MICROBE_DIGESTION_FACTOR);
		target->die();
	}
}

/*
void Microbe::graze(Food* target)
{
	if (this->canDevour(target))
	{
		this->grow(target->size);
		target->shrink(target->size);
	}
}
*/

void Microbe::starve()
{
	// create food from remains
	if (this->isPlayer)
	{
		// find new player of same species, else game over
	}
	this->die();
}

void Microbe::die()
{
	// remove this from object list
}

int Microbe::getSize() {return this->size;}
int Microbe::getSpeed() {return this->speed;}
std::string Microbe::getSpecies() {return this->species;}

bool Microbe::overlapsOther(Microbe* target)
{
	// check if this->hitbox overlaps with target->hitbox
	return false;
}
/*
bool Microbe::overlapsFood(Food* target)
{
	// check if this->hitbox overlaps with target->hitbox
	return false;
}
*/

bool Microbe::canDevour(Microbe* target)
{
	if (this->isSameSpecies(target)) {return false;}
	if (this->size * MICROBE_CANIBALISM_FACTOR < target->size ) {return false;}
	return true;
}

bool Microbe::canBeDevouredBy(Microbe* target)
{
	return target->canDevour(this);
}

bool Microbe::isSameSpecies(Microbe* target)
{
	return this->species == target->species;
}
