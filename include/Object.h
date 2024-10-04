#ifndef OBJECT_H
# define OBJECT_H
	#include "engineSetup.h"

	class Object
	{
		private:

		public:
			Object(Vector2 _position, Sprite sprite);
			Object(Vector2 _position, Sprite sprite, int layerLV);
			virtual ~Object();
			virtual void step();
			void updateHitbox();
			int			id;
			Sprite		sprite;
			Vector2		position;
			Texture2D*	texture;
			Rectangle	hitbox;
			int			frameIndex;
			int			animationSpeed;
			float		rotation;
			int			layer;

	};

#endif