#ifndef ENGINE_H
# define ENGINE_H
	#include "engineSetup.h"
	#include "Object.h"

	class Engine
	{
		private:
			int _windowHeight;
			int _windowWidth;
			int _uniqueID;
			bool _closeWindow;
			std::string _windowName;

		public:
			Engine(std::string windowName, int windowHeight, int windowWidth);
			~Engine();
			
			void loadTextureImage();
			void unloadTextureImage();
			void loop(void (*func)(Engine &));
			void closeWindow();
			void renderLoop();
			void stepLoop();
			int addObject(Object &object, bool render);

			SpriteMap 				sprites;
			TexturePath 			textures;
			std::vector<Object> 	objectList;
			std::vector<Object*> 	renderList;
			std::vector<Object*> 	uiRenderList;
	};

#endif