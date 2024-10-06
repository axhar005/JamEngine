#ifndef FIREBALL_H
# define FIREBALL_H
	#include "Nutrient.h"

	#define MICROBE_MIN_SIZE			8
	#define MICROBE_MAX_SIZE			64
	#define MICROBE_START_SIZE		16
	#define MICROBE_MIN_DIV_SIZE	32

	#define MICROBE_MIN_SPEED				1.0f
	#define MICROBE_MAX_SPEED				4.0f
	//#define MICROBE_MIN_WANDER_DIST	128

	#define MICROBE_STARVE_RATE				0.0f // to be implemented
	#define MICROBE_CANIBALISM_FACTOR	0.8f
	#define MICROBE_VEGANISM_FACTOR		0.9f
	#define MICROBE_DIGESTION_FACTOR	0.9f

	#define MICROBE_FLEE_RADIUS		128
	#define MICROBE_PURSUE_RADIUS	128
	#define MICROBE_GRAZE_RADIUS	128
	#define MICROBE_SPREAD_RADIUS	128

	#define MICROBE_GOAL_RADIUS		16

	// a class for entities that can move and interact with other entities or nutrients ( food )
	class Microbe : public Nutrient
	{
		private:
			float speed;
			bool isPlayer;
			std::string species;
			Vector2 wanderGoal;

		public:
			Microbe(Vector2 _position, Sprite _sprite, PetriDish* _petriDish, std::string _species, bool _isPlayer);
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
			void setNewWanderGoal();

			void clampPos();
			void move(Vector2 direction);
			void moveTowards(Vector2 target);
			void moveAwayFrom(Vector2 target);
			void wander();

			void becomePlayer();
			void playerDeathTransfer();

			void devour(Microbe* target);
			void graze(Nutrient* target);

			bool canGraze(Nutrient* target);
			bool canDevour(Microbe* target);
			bool canBeDevouredBy(Microbe* target);

			bool isSameSpecies(Microbe* target);
			bool hasReachedWanderGoal();

			int getSpeed();
			bool getIsPlayer();
			std::string getSpecies();
	};

	float getDistance(Vector2 start, Vector2 end);
	Vector2 getNormalisedDirection(Vector2 start, Vector2 end);
	Vector2 getNormalisedVector(Vector2 vector);

#endif