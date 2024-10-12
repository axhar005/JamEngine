#ifndef MICROBE_H
# define MICROBE_H
	#include "Nutrient.h"

	#define MICROBE_MIN_SIZE			8
	#define MICROBE_MAX_SIZE			64
	#define MICROBE_START_SIZE		16
	#define MICROBE_MIN_DIV_SIZE	32

	#define MICROBE_MIN_SPEED			1.0f
	#define MICROBE_MAX_SPEED			4.0f

	#define MICROBE_STARVE_RATE				0.0f // to be implemented
	#define MICROBE_CANIBALISM_FACTOR	0.8f
	#define MICROBE_VEGANISM_FACTOR		0.9f
	#define MICROBE_DIGESTION_FACTOR	0.9f

	#define MICROBE_GOAL_RADIUS		16.0f
	//#define MICROBE_WANDER_RADIUS	512.0f
	#define MICROBE_GRAZE_RADIUS	256.0f
	#define MICROBE_HUNT_RADIUS		128.0f
	#define MICROBE_FLEE_RADIUS		64.0f
	#define MICROBE_SPREAD_RADIUS	32.0f
	//#define MICROBE_HEARD_RADIUS	0.0f

	#define MAX_SEARCH_RADIUS		123456789.0f

	typedef enum mcrb_state
	{
		PLAYING,		// when controlled by the player
		FLEEING,		// when too close to predator
		GRAZING,		// when close enough to nutrient
		HUNTING,		// when close enough to prey
		BITING,			// when close enough to nutrient or prey
		DIVIDING,		// when big enough
		SPREADING, 	// when too close to ally
		//HEARDING,		// when too far from ally
		WANDERING, 	// default state, moves around randomly
	} mcrb_state;


	// a class for microbial entities that can move and interact with other entities or nutrients ( food )
	class Microbe : public Nutrient
	{
		private:
			float				speed;
			bool				isPlayer;
			mcrb_state	state;
			Vector2			wanderGoal;
			Nutrient*		targetGoal;
			//float				latestDistance;

		public:
			Microbe(Vector2 _position, Sprite _sprite, PetriDish* _petriDish, std::string _species, bool _isPlayer);
			virtual ~Microbe();

			void step();

			void refreshSpeed();
			void refreshState();

			// AUTOMATION
			void autoplay();

			// BASIC ACTIONS
			void grow(float amount);
			void shrink(float amount);
			void divide();
			void starve();
			void die(); // hacked to avoid object deletion bug

			// PLAYER SWAP
			void becomePlayer();
			void playerDeathTransfer();

			// WANDERING
			void setNewWanderGoal();
			void wander();

			// MOVEMENT ACTIONS
			void move(Vector2 direction);
			void moveTowards(Vector2 target);
			void moveAwayFrom(Vector2 target);

			// CONSUMPTION ACTIONS
			bool tryEat(); // for player only, since it recalculates the target each time
			bool tryConsume(Nutrient* target);
			bool tryGraze(Nutrient* target);
			bool tryDevour(Microbe* target);

			// CONSUMPTION CHECKS
			// NOTE : might lead to issues due to complexity of the concumption check logic overall
			bool canBeConsumedBy(Microbe* target);
			bool canConsume(Nutrient* target);
			bool canGraze(Nutrient* target);
			bool canDevour(Microbe* target);

			// OTHER CHECKS
			bool isSameSpecies(Microbe* target);
			bool hasReachedWanderGoal();

			// FINDERS
			Microbe*	findClosestPredator();
			Microbe*	findClosestPrey();
			Microbe*	findClosestAlly();
			Nutrient*	findClosestNutrient();

			// ACCESSORS
			float getSpeed();
			bool	getIsPlayer();
	};

#endif