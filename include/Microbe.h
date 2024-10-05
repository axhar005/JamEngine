#ifndef FIREBALL_H
# define FIREBALL_H
	#include "Nutrient.h"

	#define MICROBE_MIN_SIZE 8
	#define MICROBE_MAX_SIZE 256
	#define MICROBE_START_SIZE 16
	#define MICROBE_MIN_DIV_SIZE 32

	#define MICROBE_MIN_SPEED 2
	#define MICROBE_MAX_SPEED 8
	#define MICROBE_MIN_WANDER_DIST 128

	#define MICROBE_STARVE_RATE 0 // to be implemented
	#define MICROBE_CANIBALISM_FACTOR 0.8f
	#define MICROBE_DIGESTION_FACTOR 0.9f

	#define MICROBE_GOAL_RADIUS 8

	// NOTE : add PetriDish class

	// a class for entities that can move and interact with other entities or nutrients ( food )
	class Microbe : public Nutrient // make nutrient object too
	{
		private:
			int speed;
			bool isPlayer;
			std::string species;
			Vector2 wanderGoal;

		public:
			Microbe(Vector2 _position, Sprite _sprite, std::string _species, bool _isPlayer);
			~Microbe();

			void step();

			void refreshSpeed();

			void grow(int amount);
			void shrink(int amount);
			void divide();
			void starve();
			void die();

			Microbe* findClosestPredator();
			Microbe* findClosestPrey();
			Nutrient* findClosestNutrient();
			void getNewWanderGoal();

			void move(Vector2 direction);
			void moveTowards(Vector2 target);
			void moveAwayFrom(Vector2 target);
			void wander();

			void devour(Microbe* target);
			void graze(Nutrient* target);

			bool overlapsOther(Microbe* target);
			bool overlapsNutrient(Nutrient* target);

			bool canGraze(Nutrient* target);
			bool canDevour(Microbe* target);
			bool canBeDevouredBy(Microbe* target);

			bool isSameSpecies(Microbe* target);
			bool hasReachedWanderGoal();

			int getSpeed();
			std::string getSpecies();
	};

	Vector2 getNormalisedDirection(Vector2 start, Vector2 end);

	// NOTE : add way to add/remove microbes from a global list

#endif