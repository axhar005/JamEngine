#ifndef NUTRIENT_H
# define NUTRIENT_H
	#include "../include/Object.h"
	#include <raylib.h>
	#include "engineSetup.h"

	#define NUTRIENT_MIN_SIZE 4
	#define NUTRIENT_MAX_SIZE 16

	#define NUTRIENT_GROWTH_RATE 0.0f // to be implemented

	class PetriDish;

	// a class for food objects, and the parent class to microbes ( entities )
	class Nutrient : public Object
	{
		private:
			void setRandomSize();

		protected:
			float size;
			PetriDish* petriDish;

		public:
			Nutrient(Vector2 _position, Sprite _sprite, PetriDish *_petriDish, int _size, bool addToPetriDish = true);
			~Nutrient();

			void step();

			void refreshSize();
			void refreshPos();

			void grow(int amount);
			//void shrink(int amount);
			//void divide();
			void die();

			int getSize();
			PetriDish* getPetriDish();

			bool overlapsOther(Nutrient* other);

			bool isOnEdge();
	};

	// NOTE : fuse Nutrients that overlap?

#endif