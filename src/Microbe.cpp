#include "../include/Microbe.h"
#include "../include/PetriDish.h"
#include "../include/Engine.h"

Microbe::Microbe(Vector2 _position, Sprite _sprite, PetriDish* _petriDish, std::string _species, bool _isPlayer) :
	Nutrient(_position, _sprite, _petriDish, MICROBE_START_SIZE, false)
{
	this->petriDish = _petriDish;
	this->petriDish->addMicrobe(this);
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

		Microbe* newMicrobe = new Microbe(this->position, this->sprite, this->petriDish, this->species, false);
		newMicrobe->size = this->size;
		newMicrobe->refreshSpeed();

		this->petriDish->addMicrobe(newMicrobe);
	}
}

void Microbe::starve()
{
	if (this->isPlayer)
	{
		this->playerDeathTransfer();
	}

	// NOTE : use nutrient sprite instead
	Nutrient* nutrient = new Nutrient(this->position, Engine::getInstance().getSprite("Nutrient"), this->petriDish, this->size);
	this->petriDish->addNutrient(nutrient);
	this->petriDish->removeMicrobe(this);
	this->die();
}

void Microbe::die()
{
	this->petriDish->removeMicrobe(this);

	if (this->isPlayer)
	{
		this->playerDeathTransfer();
	}

	delete this;
}

Microbe* Microbe::findClosestPredator()
{
	int closest_distance = 999999;
	Microbe* target = nullptr;

	for (Microbe* predator : this->petriDish->getMicrobes())
	{
		if (this->canBeDevouredBy(predator))
		{
			int distance = getDistance(this->position, predator->position);
			if (distance < closest_distance)
			{
				closest_distance = distance;
				target = predator;
			}
		}
	}
	return target;
}

Microbe* Microbe::findClosestPrey()
{
	int closest_distance = 999999;
	Microbe* target = nullptr;

	for (Microbe* prey : this->petriDish->getMicrobes())
	{
		if (this->canDevour(prey))
		{
			int distance = getDistance(this->position, prey->position);
			if (distance < closest_distance)
			{
				closest_distance = distance;
				target = prey;
			}
		}
	}
	return target;
}


Nutrient* Microbe::findClosestNutrient()
{
	int closest_distance = 999999;
	Nutrient* target = nullptr;

	for (Nutrient* nutrient : this->petriDish->getNutrients())
	{
		int distance = getDistance(this->position, nutrient->position);
		if (distance < closest_distance)
		{
			closest_distance = distance;
			target = nutrient;
		}
	}
	return target;
}

void Microbe::setNewWanderGoal() {this->wanderGoal = this->petriDish->getRandomPos();}

void Microbe::clampPos()
{
	Vector2 center;
	center.x = 0;
	center.y = 0;

	if ( getDistance(this->position, center) >= this->petriDish->getRadius())
	{
		Vector2 newPosDir = getNormalisedDirection(center, this->position);
		this->position.x = newPosDir.x * this->petriDish->getRadius();
		this->position.y = newPosDir.y * this->petriDish->getRadius();
	}
}

void Microbe::move(Vector2 direction)	// NOTE : assumes direction is normalized
{
	this->position.x = this->position.x + direction.x * this->speed;
	this->position.y = this->position.y + direction.y * this->speed;

	this->clampPos();
	this->refreshPos();
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
	// NOTE : make sure to avoid walls
	// if found predators of other species, move away from them
	// else if found nutrients, move towards them
	// else if found prey of other species, move towards them
	// else if found same species, move away from them
	// else if none found, use wander goal

	Nutrient* target;

	// insert logic to avoid walls

	target = this->findClosestPredator();
	if (target != nullptr && getDistance(this->position, target->position) < MICROBE_FLEE_RADIUS)
	{
		this->moveAwayFrom(target->position);
		return;
	}

	target = this->findClosestNutrient();
	if (target != nullptr && getDistance(this->position, target->position) < MICROBE_GRAZE_RADIUS)
	{
		this->moveTowards(target->position);
		if (this->overlapsOther(target))
			this->graze(target);
		return;
	}

	target = this->findClosestPrey();
	if (target != nullptr && getDistance(this->position, target->position) < MICROBE_PURSUE_RADIUS)
	{
		this->moveTowards(target->position);
		return;
	}

	// insert logic to get away from same species

	if (this->hasReachedWanderGoal())
		this->setNewWanderGoal();

	this->moveTowards(this->wanderGoal);
}

void Microbe::becomePlayer()
{
	this->isPlayer = true;
	this->sprite = Engine::getInstance().getSprite("Player");
}

void Microbe::playerDeathTransfer()
{
	Microbe* newPlayer = nullptr;
	for (Microbe* microbe : this->petriDish->getMicrobes())
	{
		if (microbe->getSpecies() != this->species)
			continue;
		if (microbe == this)
			continue;

		newPlayer = microbe;
		break;
	}

	if (newPlayer != nullptr)
		newPlayer->becomePlayer();
	else
	{
		// GAME OVER
		return;
	}
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

bool Microbe::canGraze(Nutrient* target)
{
	if (this->size * MICROBE_VEGANISM_FACTOR < target->getSize()) {return false;}
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
bool Microbe::getIsPlayer() {return this->isPlayer;}
std::string Microbe::getSpecies() {return this->species;}
