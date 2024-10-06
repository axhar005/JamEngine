#ifndef PLAYER_H
# define PLAYER_H
	#include "engineSetup.h"
	#include "../include/Object.h"


	class Player : public Object
	{
		private:

		public:
			Player(Vector2 _position, Sprite _sprite, bool _visible);
			Player(Vector2 _position, Sprite _sprite, bool _visible, int _layerLV);
			~Player();
			void 	step();
			void 	draw();

			bool showHitbox;
	};

#endif