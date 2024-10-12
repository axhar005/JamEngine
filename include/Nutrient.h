#ifndef NUTRIENT_H
# define NUTRIENT_H
	#include "../include/Object.h"
	#include <raylib.h>
	#include "engineSetup.h"
	#include "microAddons.h"

	#define NUTRIENT_MIN_SIZE 4.0f
	#define NUTRIENT_MAX_SIZE 16.0f

	#define NUTRIENT_GROWTH_RATE 0.0f // to be implemented

	class PetriDish;

	// a class for food objects, and the parent class to microbes ( entities )
	class Nutrient : public Object
	{
		private:
			void setRandomSize();

		protected:
			PetriDish*	petriDish;
			float				size;
			std::string	species;

		public:
			Nutrient(Vector2 _position, Sprite _sprite, PetriDish *_petriDish, float _size, bool addToPetriDish = true);
			virtual ~Nutrient();

			void step();

			void refreshSize();
			void refreshPos();
			void clampPos();

			void grow(float amount);
			void shrink(float amount);
			//void divide();
			void die();

			bool overlapsOther(Nutrient* other);
			bool isOnEdge();

			// NOTE : might lead to issues due to complexity of the concumption check logic overall
			bool canBeConsumedBy(Nutrient* target);
			bool canConsume(Nutrient* target);

			float 			getSize();
			Vector2&		getPosition();
			std::string	getSpecies();
			PetriDish*	getPetriDish();
			float				getDistanceTo(Nutrient* target);
			float				getTaxiCabDistanceTo(Nutrient* target);
	};

	// NOTE : fuse Nutrients that overlap?

#endif