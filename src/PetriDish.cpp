#include "../include/PetriDish.h"
#include "../include/Nutrient.h"
#include "../include/Microbe.h"

PetriDish::PetriDish(Vector2 _position, Sprite _sprite, int _radius) :
	Object(_position, _sprite)
{
	this->radius = _radius;
}

PetriDish::~PetriDish()
{
}

void PetriDish::step()
{
	// spawn nutrients when there's too few

	for (Nutrient* nutrient : this->nutrients)
		nutrient->step();

	for (Microbe* microbe : this->microbes)
		microbe->step();
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

std::vector<Nutrient*> PetriDish::getNutrients() {return this->nutrients;}
std::vector<Microbe*> PetriDish::getMicrobes() {return this->microbes;}

int PetriDish::getRadius() {return this->radius;}