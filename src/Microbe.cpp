#include "../include/Microbe.h"
#include "../include/PetriDish.h"
#include "../include/Engine.h"
#include <cmath>
#include <raylib.h>

Microbe::Microbe(Vector2 _position, Sprite _sprite, PetriDish* _petriDish, std::string _species, bool _isPlayer) :
	Nutrient(_position, _sprite, _petriDish, MICROBE_START_SIZE, false)
{
	this->petriDish = _petriDish;
	this->petriDish->addMicrobe(this);
	this->refreshSpeed(); //	makes speed invertly proportional to its size
	this->refreshSize(); //		sets hitbox size to size
	this->refreshPos(); //		sets hitbox position to position ( clamped to petriDish )
	this->wanderGoal = this->petriDish->getRandomPos();

	this->species = _species;
	this->isPlayer = _isPlayer;
}

Microbe::~Microbe()
{
}

void Microbe::step()
{
	Engine& e = Engine::getInstance();
	if (e.run) {
		this->shrink(MICROBE_STARVE_RATE); // lose size each tick

		this->refreshPos();
		this->refreshSize();
		this->refreshSpeed();

		if (this->isPlayer)
		{
			// get user input
			const Vector2 dir = {
				(float)IsKeyDown(KEY_D) - (float)IsKeyDown(KEY_A),
				(float)IsKeyDown(KEY_S) - (float)IsKeyDown(KEY_W)};
			this->move(dir);

			if (IsKeyPressed(KEY_SPACE))
				this->tryEat();
		}
		else
			this->autoplay();
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

void Microbe::grow(float amount)
{
	this->size += amount;
	if (this->size > MICROBE_MAX_SIZE)
	{
		this->size = MICROBE_MAX_SIZE;
		this->refreshSpeed();
	}
}

void Microbe::shrink(float amount)
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
		this->playerDeathTransfer();

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
		this->playerDeathTransfer();

	delete this;
}

Microbe* Microbe::findClosestPredator()
{
	float closest_distance = MAX_SEARCH_RADIUS;
	Microbe* target = nullptr;

	for (Microbe* predator : this->petriDish->getMicrobes())
	{
		if (this->canBeDevouredBy(predator))
		{
			float distance = getDistance(this->position, predator->position);
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
	float closest_distance = MAX_SEARCH_RADIUS;
	Microbe* target = nullptr;

	for (Microbe* prey : this->petriDish->getMicrobes())
	{
		if (this->canDevour(prey))
		{
			float distance = getDistance(this->position, prey->position);
			if (distance < closest_distance)
			{
				closest_distance = distance;
				target = prey;
			}
		}
	}
	return target;
}

Microbe* Microbe::findClosestAlly()
{
	float closest_distance = MAX_SEARCH_RADIUS;
	Microbe* target = nullptr;

	for (Microbe* ally : this->petriDish->getMicrobes())
	{
		if (ally != this && this->isSameSpecies(ally))
		{
			float distance = getDistance(this->position, ally->position);
			if (distance < closest_distance)
			{
				closest_distance = distance;
				target = ally;
			}
		}
	}
	return target;
}

Nutrient* Microbe::findClosestNutrient()
{
	float closest_distance = MAX_SEARCH_RADIUS;
	Nutrient* target = nullptr;

	for (Nutrient* nutrient : this->petriDish->getNutrients())
	{
		float distance = getDistance(this->position, nutrient->position);
		if (distance < closest_distance)
		{
			closest_distance = distance;
			target = nutrient;
		}
	}
	return target;
}

void Microbe::setNewWanderGoal() {this->wanderGoal = this->petriDish->getRandomPos();}

void Microbe::move(Vector2 direction)
{
	Vector2 vector = getNormalisedVector(direction);
	//printf("Moving by %f, %f\n", vector.x, vector.y);

	this->position.x += (vector.x * this->speed);
	this->position.y += (vector.y * this->speed);

	this->refreshPos();
}

void Microbe::moveTowards(Vector2 target)
{
	//printf("Moving towards %f, %f\n", target.x, target.y);
	Vector2 direction = Vector2{target.x - this->position.x, target.y - this->position.y};
	this->move(direction);
}

void Microbe::moveAwayFrom(Vector2 target)
{
	//printf("Moving away from %f, %f\n", target.x, target.y);
	Vector2 direction = Vector2{this->position.x - target.x, this->position.y - target.y};
	this->move(direction);
}

void Microbe::wander()
{
	if (this->hasReachedWanderGoal())
		this->setNewWanderGoal();
	this->moveTowards(this->wanderGoal);
}

void Microbe::autoplay()
{
	// NOTE : make sure to avoid walls
	// if found predators of other species, move away from them
	// else if found same species, move away from them
	// else if found nutrients, move towards them
	// else if found prey of other species, move towards them
	// else if none found, use wander goal

	Nutrient* target;
	float distance;

	// insert logic to avoid walls

	target = this->findClosestPredator();
	if (target != nullptr)
		distance = getDistance(this->position, target->position);

	if (target != nullptr && distance < MICROBE_FLEE_RADIUS)
	{
		this->moveAwayFrom(target->position);
		return;
	}

	target = this->findClosestNutrient();
	if (target != nullptr)
		distance = getDistance(this->position, target->position);

	if (target != nullptr && distance < MICROBE_GRAZE_RADIUS)
	{
		this->moveTowards(target->position);
		if (distance < MICROBE_GOAL_RADIUS)
			this->tryGraze(target);
		return;
	}

	if (this->size > MICROBE_MIN_DIV_SIZE)
	{
		printf("dividin\n");
		this->divide();
		return;
	}

	target = this->findClosestPrey();
	if (target != nullptr)
		distance = getDistance(this->position, target->position);

	if (target != nullptr && distance < MICROBE_PURSUE_RADIUS)
	{
		this->moveTowards(target->position);
		//if (distance < MICROBE_GOAL_RADIUS)
			//this->tryDevour((Microbe*)target);
		return;
	}

	target = this->findClosestAlly();
	if (target != nullptr)
		distance = getDistance(this->position, target->position);

	if (target != nullptr && distance < MICROBE_SPREAD_RADIUS)
	{
		this->wander();
		return;
	}
	this->wander();
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
		// TODO : GAME OVER
		return;
	}
}

void Microbe::tryEat()
{
	Nutrient* target = this->findClosestNutrient();
	if (target != nullptr)
		this->tryGraze(target);

	//Microbe* prey = this->findClosestPrey(); // segfaults
	//if (target != nullptr)
		//this->tryDevour(prey);
}

void Microbe::tryGraze(Nutrient* target)
{
	if (this->canGraze(target))
	{
		this->grow(target->getSize());
		target->die();
	}
}

void Microbe::tryDevour(Microbe* target)
{
	if (this->canDevour(target))
	{
		this->grow(target->getSize() * MICROBE_DIGESTION_FACTOR);
		target->die();
	}
}

bool Microbe::canGraze(Nutrient* target)
{
	if (!this->overlapsOther(target)) {return false;}
	if (this->size * MICROBE_VEGANISM_FACTOR < target->getSize()) {return false;}
	return true;
}

bool Microbe::canDevour(Microbe* target)
{
	if (this->isSameSpecies(target)) {return false;}
	if (!this->overlapsOther(target)) {return false;}
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

float Microbe::getSpeed() {return this->speed;}
bool Microbe::getIsPlayer() {return this->isPlayer;}
std::string Microbe::getSpecies() {return this->species;}
