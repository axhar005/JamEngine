#include "../../include/microbial/microSetup.h"

Microbe::Microbe(Vector2 _position, Sprite _sprite, PetriDish* _petriDish, std::string _species, bool _isPlayer) :
	Nutrient(_position, _sprite, _petriDish, MICROBE_START_MASS, false)
{
	this->petriDish = _petriDish;
	this->petriDish->addMicrobe(this);
	this->refreshSpeed(); //	makes speed invertly proportional to its mass
	this->refreshSize(); //		sets hitbox dims to sqrt(mass)
	this->refreshPos(); //		sets hitbox position to position ( clamped to petriDish )
	this->wanderGoal = this->petriDish->getRandomPos();

	this->species = _species;
	this->isPlayer = _isPlayer;
}

Microbe::~Microbe()
{
}

void Microbe::playerControls()
{
	static bool sneak;

	// hacky af but I'm lazy rn. implement better later
	if (IsKeyPressed(KEY_LEFT_SHIFT ))
		sneak = !sneak;
	if (sneak)
		this->speed = MICROBE_MIN_SPEED;

	// get user input
	const Vector2 dir = {
		(float)IsKeyDown(KEY_D) - (float)IsKeyDown(KEY_A),
		(float)IsKeyDown(KEY_S) - (float)IsKeyDown(KEY_W)};
	this->move(dir);

	//debug actions
	if (IsKeyPressed(KEY_R))
		this->divide();
	else if (IsKeyPressed(KEY_LEFT_CONTROL))
		this->playerDeathTransfer();

	if (IsKeyPressed(KEY_KP_EQUAL))
		this->grow(16);
	else if (IsKeyPressed(KEY_KP_SUBTRACT))
		this->shrink(16);

	if (IsKeyPressed(KEY_SPACE))
		if (this->tryEat())
			printf("Player ate something\n");
}

void Microbe::step()
{
	this->shrink(MICROBE_STARVE_RATE); // lose mass each tick

	this->refreshPos();
	this->refreshSize();
	this->refreshSpeed();

	if (this->isPlayer)
		this->playerControls();
	else
		this->autoplay();
}

void Microbe::refreshSpeed()
{
	// speed is inversely proportional to mass, and linearly distributed between min and max speed

	float speed_range = MICROBE_MAX_SPEED - MICROBE_MIN_SPEED;
	float mass_range = MICROBE_MAX_MASS - MICROBE_MIN_MASS;

	float norm_mass = (this->mass - MICROBE_MIN_MASS) / mass_range;

	this->speed = MICROBE_MIN_SPEED + ((1.0f - norm_mass) * speed_range);
}

void Microbe::refreshState()
{
	Nutrient*	target;

	target = this->findClosestPredator();
	if (target != nullptr)
	{
		this->targetGoal = target;
		this->state = FLEEING;
		return;
	}

	target = this->findClosestNutrient();
	if (target != nullptr)
	{
		this->targetGoal = target;
		if (this->overlapsOther(target))
			this->state = BITING;
		else
			this->state = GRAZING;
		return;
	}
/*
	if (this->mass > MICROBE_MIN_DIV_MASS) // lags the game real fast since entity count isn't bounded
	{
		this->state = DIVIDING;
		return;
	}
*/

	target = this->findClosestPrey();
	if (target != nullptr)
	{
		this->targetGoal = target;
		//if (this->overlapsOther(target)) // killing smthg crashes the game as of 2024/10/12 - LL
			//this->state = BITING;
		//else
			this->state = HUNTING;
		return;
	}

	target = this->findClosestAlly();
	if (target != nullptr)
	{
		this->targetGoal = target;
		this->state = SPREADING;
		return;
	}

	this->state = WANDERING;
}

void Microbe::autoplay()
{

	this->refreshState();

	switch (this->state)
	{
		case FLEEING:
			this->setName("runnin");
			this->moveAwayFrom(this->targetGoal->getPosition());
			break;

		case GRAZING:
			this->setName("grazin");
			this->moveTowards(this->targetGoal->getPosition());
			break;

		case HUNTING:
			this->setName("huntin");
			this->moveTowards(this->targetGoal->getPosition());
			break;

		case BITING:
			this->setName("bitin");
			tryConsume(this->targetGoal);
			break;

		case DIVIDING:
			this->setName("dividin");
			this->divide();
			break;

		case SPREADING:
			this->setName("spreadin");
			this->wander();
			break;

		default: // WANDERING
			this->setName("wanderin");
			this->wander();
			break;
	}
}

void Microbe::grow(float amount)
{
	this->mass += amount;
	if (this->mass > MICROBE_MAX_MASS)
	{
		this->mass = MICROBE_MAX_MASS;
		this->refreshSpeed();
	}
}

void Microbe::shrink(float amount)
{
	this->mass -= amount;
	if (this->mass < MICROBE_MIN_MASS)
	{
		this->starve();
	}
}

void Microbe::divide()
{
	if (this->mass > MICROBE_MIN_DIV_MASS)
	{
		this->mass /= 2;
		this->refreshSpeed();

		Microbe* newMicrobe = new Microbe(this->position, this->sprite, this->petriDish, this->species, false);
		newMicrobe->mass = this->mass;
		newMicrobe->refreshSpeed();

		this->petriDish->addMicrobe(newMicrobe);
	}
}

void Microbe::starve()
{
	if (this->isPlayer)
		this->playerDeathTransfer();

	// NOTE : use nutrient sprite instead
	Nutrient* nutrient = new Nutrient(this->position, Engine::getInstance().getSprite("Nutrient"), this->petriDish, this->mass);
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

void Microbe::setNewWanderGoal() {this->wanderGoal = this->petriDish->getRandomPos();}

void Microbe::wander()
{
	if (this->hasReachedWanderGoal())
		this->setNewWanderGoal();
	this->moveTowards(this->wanderGoal);
}

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

bool Microbe::tryEat()
{
	printf("Player tryna eat frfr\n");

	Nutrient* target = this->findClosestNutrient();
	if (target != nullptr)
		return this->tryGraze(target);

	//Microbe* prey = this->findClosestPrey(); // segfaults
	//if (target != nullptr)
		//return this->tryDevour(prey);

	return false;
}

bool Microbe::tryConsume(Nutrient* target)
{
	// NOTE : might lead to bugs due to casting Nutrient as Microbe
	if (this->tryGraze(target)) return true;
	if (this->tryDevour((Microbe*)target)) return true;

	return false;
}

bool Microbe::tryGraze(Nutrient* target)
{
	if (this->canGraze(target))
	{
		this->grow(target->getMass());
		target->die(); // hacked to avoid caling delete on a Nutrient object
		return true;
	}
	return false;
}

bool Microbe::tryDevour(Microbe* target)
{
	if (this->canDevour(target))
	{
		this->grow(target->getMass() * MICROBE_DIGESTION_FACTOR);
		target->die(); // segfaults as of 2024/10/12 - LL
		return true;
	}
	return false;
}

bool Microbe::canBeConsumedBy(Microbe* target) {return target->canConsume(this);}
bool Microbe::canConsume(Nutrient* target)
{
	// NOTE : might lead to bugs due to casting Nutrient as Microbe
	if (this->canGraze(target)) {return true;}
	if (this->canDevour((Microbe*)target)) {return true;}

	return false;
}

bool Microbe::canGraze(Nutrient* target)
{
	if (target->getSpecies() != "Nutrient") {return false;}
	if (!this->overlapsOther(target)) {return false;}
	//if (this->mass * MICROBE_VEGANISM_FACTOR < target->getMass()) {return false;}
	return true;
}

bool Microbe::canDevour(Microbe* target)
{
	if (this->isSameSpecies(target)) {return false;}
	if (target->getSpecies() == "Nutrient") {return false;}
	if (!this->overlapsOther(target)) {return false;}
	if (this->mass * MICROBE_CANIBALISM_FACTOR < target->getMass() ) {return false;}
	return true;
}


// ================ OTHER CHECKS ================

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

// ================ FINDERS ================

Microbe* Microbe::findClosestPredator()
{
	float distance = MAX_SEARCH_RADIUS;
	float closest_distance = MICROBE_FLEE_RADIUS;
	Microbe* target = nullptr;

	for (Microbe* predator : this->petriDish->getMicrobes())
	{
		if (this->canBeConsumedBy(predator))
		{
			// optimisation to avoid unnecessary calculations
			if (this->getTaxiCabDistanceTo(predator) > distance * root2)
				continue;
			distance = this->getDistanceTo(predator);
			if (distance < closest_distance)
			{
				closest_distance = distance;
				target = predator;
			}
		}
	}
	//this->latestDistance = closest_distance;
	return target;
}

Microbe* Microbe::findClosestPrey()
{
	float closest_distance = MICROBE_HUNT_RADIUS;
	Microbe* target = nullptr;

	for (Microbe* prey : this->petriDish->getMicrobes())
	{
		if (this->canDevour(prey))
		{
			float distance = this->getDistanceTo(prey);
			if (distance < closest_distance)
			{
				closest_distance = distance;
				target = prey;
			}
		}
	}
	//this->latestDistance = closest_distance;
	return target;
}

Microbe* Microbe::findClosestAlly()
{
	float closest_distance = MICROBE_SPREAD_RADIUS;
	Microbe* target = nullptr;

	for (Microbe* ally : this->petriDish->getMicrobes())
	{
		if (ally != this && this->isSameSpecies(ally))
		{
			float distance = this->getDistanceTo(ally);
			if (distance < closest_distance)
			{
				closest_distance = distance;
				target = ally;
			}
		}
	}
	//this->latestDistance = closest_distance;
	return target;
}

Nutrient* Microbe::findClosestNutrient()
{
	float closest_distance = MICROBE_GRAZE_RADIUS;
	Nutrient* target = nullptr;

	for (Nutrient* nutrient : this->petriDish->getNutrients())
	{
		float distance = this->getDistanceTo(nutrient);
		if (distance < closest_distance)
		{
			closest_distance = distance;
			target = nutrient;
		}
	}
	//this->latestDistance = closest_distance;
	return target;
}

// ================ ACCESSORS ================

float Microbe::getSpeed() {return this->speed;}
bool Microbe::getIsPlayer() {return this->isPlayer;}