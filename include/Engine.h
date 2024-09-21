#ifndef ENGINE_H
# define ENGINE_H
	#include "engineSetup.h"
	#include "Object.h"

	class Engine
	{
		private:
			Engine(std::string windowName, int windowHeight, int windowWidth);
			~Engine();
			Engine(const Engine&) = delete;
			Engine& operator=(const Engine&) = delete;
			Engine(Engine&&) = delete;
			Engine& operator=(Engine&&) = delete;
			void loadTextureImage();
			void unloadTextureImage();
			void renderLoop();
			void stepLoop();
			int _windowHeight;
			int _windowWidth;
			int _uniqueID;
			bool _closeWindow;
			std::string _windowName;
			static Engine* _instance;

		public:
			static Engine& getInstance();
			static void initInstance(std::string windowName, int windowHeight, int windowWidth);
			void loop(void (*func)(Engine &));
			void closeWindow();
			int addObject(Object& object, bool render);
			SpriteMap 				sprites;
			TexturePath 			textures;
			std::vector<Object> 	objectList;
			std::vector<Object*> 	renderList;
			std::vector<Object*> 	uiRenderList;
	};

#endif