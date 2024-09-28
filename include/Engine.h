#ifndef ENGINE_H
# define ENGINE_H
	#include "engineSetup.h"
	#include "Object.h"

	class Engine
	{
		private:
			int				_windowHeight;
			int				_windowWidth;
			int				_uniqueID;
			bool			_closeWindow;
			std::string		_windowName;
			Camera2D*		_2DCamera;

		public:
			Engine(std::string windowName, int windowHeight, int windowWidth);
			~Engine();
			
			void set2DCamera(Camera2D& camera);
			void Remove2DCamera(void);
			void loadTextureImage();
			void unloadTextureImage();
			void loop(void (*func)(Engine &));
			void closeWindow();
			void stepLoop();
			int  addObject(Object &object, bool render);
			void Render(void);

			SpriteMap				sprites;
			TexturePath				textures;
			std::vector<Object>		objectList;
			std::vector<Object*>	renderList;
			std::vector<Object*>	uiRenderList;
			Camera2D*				camera;
	};

#endif