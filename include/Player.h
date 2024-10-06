#ifndef PLAYER_H
# define PLAYER_H
	#include "engineSetup.h"
	#include "../include/Object.h"


	class Player : public Object
	{
		private:

		public:
			Player(Vector2 _position);
			Player(Vector2 _position, Sprite _sprite);
			Player(Vector2 _position, Sprite _sprite, int _layerLV);
			~Player();
			void 	step();
			void 	draw();

			bool showHitbox;
	};

#endif