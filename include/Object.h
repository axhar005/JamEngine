#ifndef OBJECT_H
# define OBJECT_H
	#include "engineSetup.h"

	class Object
	{
		private:

		public:
			Object(Vector2 _position, Sprite sprite);
			virtual ~Object();
			virtual void step();
			Vector2		position;
			Sprite		sprite;
			Texture2D*	texture;
			Rectangle	hitbox;
			int			frameIndex;
			int			animationSpeed;
			int			id;
	};

#endif