#ifndef FIREBALL_H
# define FIREBALL_H
	#include "../include/Object.h"
	#include "engineSetup.h"

	class Fireball : public Object
	{
		private:

		public:
			Fireball(Vector2 _position, Sprite sprite);
			~Fireball();
			void step();
	};

#endif