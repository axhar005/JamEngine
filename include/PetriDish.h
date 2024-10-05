#ifndef PETRIDISH_H
# define PETRIDISH_H
	#include "Object.h"
	#include <raylib.h>
	#include "engineSetup.h"

	#ifndef NUTRIENT_H
		class Nutrient;
	#endif

	#ifndef MICROBE_H
		class Microbe;
	#endif

	// the playfield that contains our Nutrients and Microbes
	class PetriDish : public Object
	{
		private:
			int radius;
			std::vector<Nutrient*> nutrients;
			std::vector<Microbe*> microbes;

		public:
			PetriDish(Vector2 _position, Sprite _sprite, int _radius);
			~PetriDish();

			void addNutrient(Nutrient* nutrient);
			void addMicrobe(Microbe* microbe);

			void removeNutrient(Nutrient* nutrient);
			void removeMicrobe(Microbe* microbe);

			void spawnPlayer(std::string species, Sprite _sprite);
			void spawnMicrobe(std::string species, Sprite _sprite, int count);
			void spawnNutrient(int count, Sprite _sprite);

			std::vector<Nutrient*> getNutrients();
			std::vector<Microbe*> getMicrobes();
			Microbe* getPlayer();

			int getRadius();
			Vector2 getRandomPos();
	};

#endif