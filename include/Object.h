#ifndef OBJECT_H
# define OBJECT_H
	#include "engineSetup.h"

	class Object
	{
		private:
			std::string		 name;

		protected:
			Object(Vector2 _position);

		public:
			Object(Vector2 _position, Sprite _sprite);
			Object(Vector2 _position, Sprite _sprite, int _layerLV);
			virtual 		~Object();
			virtual void 	step();
			virtual void 	draw();
			void 			update();
			virtual void	setName(const char* _name);
			virtual const	std::string&	getName(void);
			int				id;
			Sprite			sprite;
			Vector2			position;
			Texture2D*		texture;
			Hitbox			hitbox;
			int				frameIndex;
			int				animationSpeed;
			float			rotation;
			int				layer;
	};

#endif