#ifndef FIREBALL_H
# define FIREBALL_H
	#include "../include/Object.h"
#include <raylib.h>
	#include "engineSetup.h"


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

	class Microbe : public Object // make food object too
	{
		private:
			int size;
			int speed;
			bool isPlayer;
			std::string species;
			Vector2 wanderGoal;

		public:
			Microbe(Vector2 _position, Sprite sprite, std::string _species, bool _isPlayer);
			~Microbe();

			void step();

			void grow(int amount);
			void shrink(int amount);
			void divide();

			void refreshSpeed();

			Microbe* findClosestPredator();
			Microbe* findClosestPrey();
			//Food* findClosestFood(); //					make food object too
			void getNewWanderGoal();

			void move(Vector2 direction);
			void moveTowards(Vector2 target);
			void moveAwayFrom(Vector2 target);
			void wander();

			void devour(Microbe* target);
			//void graze(Food* target); //				make food object too
			void starve();
			void die();

			int getSize();
			int getSpeed();

			std::string getSpecies();

			bool overlapsOther(Microbe* target);
			//bool overlapsFood(Food* target); //	make food object too

			bool canDevour(Microbe* target);
			bool canBeDevouredBy(Microbe* target);

			bool isSameSpecies(Microbe* target);
	};

	// NOTE : add way to add/remove microbes from a global list

#endif