#include "../include/PetriDish.h"
#include "../include/Nutrient.h"
#include "../include/Microbe.h"

PetriDish::PetriDish(Vector2 _position, Sprite _sprite, int _radius) :
	Object(_position, _sprite, false)
{
	this->radius = _radius;
}

PetriDish::~PetriDish()
{
}

void PetriDish::addNutrient(Nutrient* nutrient) {this->nutrients.push_back(nutrient);}
void PetriDish::addMicrobe(Microbe* microbe) {this->microbes.push_back(microbe);}

void PetriDish::removeNutrient(Nutrient* nutrient)
{
	this->nutrients.erase(std::remove(this->nutrients.begin(), this->nutrients.end(), nutrient), this->nutrients.end());
}

void PetriDish::removeMicrobe(Microbe* microbe)
{
	this->microbes.erase(std::remove(this->microbes.begin(), this->microbes.end(), microbe), this->microbes.end());
}

void PetriDish::spawnPlayer(std::string species, Sprite _sprite)
{
	Microbe* player = new Microbe(this->getRandomPos(), _sprite, this, species, true);
	this->addMicrobe(player);
}

void PetriDish::spawnMicrobe(std::string species, Sprite _sprite, int count)
{
	for (int i = 0; i < count; i++)
	{
		Microbe* microbe = new Microbe(this->getRandomPos(), _sprite, this, species, false);
		this->addMicrobe(microbe);
	}
}

void PetriDish::spawnNutrient(Sprite _sprite, int count)
{
	for (int i = 0; i < count; i++)
	{
		Nutrient* nutrient = new Nutrient(this->getRandomPos(), _sprite, this, 0);
		this->addNutrient(nutrient);
	}
}

std::vector<Nutrient*> PetriDish::getNutrients() {return this->nutrients;}
std::vector<Microbe*> PetriDish::getMicrobes() {return this->microbes;}

Microbe* PetriDish::getPlayer()
{
	for (Microbe* microbe : this->microbes)
	{
		if (microbe->getIsPlayer())
			return microbe;
	}
	return nullptr;
}

int PetriDish::getRadius() {return this->radius;}

// NOTE : biased towards center and diagonal directions
Vector2 PetriDish::getRandomPos()
{
	Vector2 pos;
	pos.x = GetRandomValue( -this->getRadius(), this->getRadius());
	pos.y = GetRandomValue( -this->getRadius(), this->getRadius());

	pos = getNormalisedDirection(Vector2{0, 0}, pos);
	int distance = GetRandomValue(0, this->getRadius());

	pos.x *= distance;
	pos.y *= distance;

	return pos;
}