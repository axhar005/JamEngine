#ifndef OBJECT_H
# define OBJECT_H
	#include "engineSetup.h"

	class Object
	{
		private:
			std::string		name;
			bool			visible;

		protected:
			Object(Vector2 _position, bool _visible);

		public:
			Object(Vector2 _position, Sprite _sprite, bool _visible);
			Object(Vector2 _position, Sprite _sprite, bool _visible, int _layerLV);
			virtual 		~Object();
			virtual void 	step();
			virtual void 	draw();
			void 			update();
			virtual void	setName(const char* _name);
			virtual const	std::string&	getName(void);
			int 			getLayer();
			void 			setLayer(int _layerLV);
			bool 			getVisible();
			void 			setVisible(bool _visible);
			void			setSprite(std::string name);

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