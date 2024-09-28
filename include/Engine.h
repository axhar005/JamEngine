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
			Engine(Engine&&) = delete;
			Engine& operator=(const Engine&) = delete;
			Engine& operator=(Engine&&) = delete;
			void  unloadTextureImage();
			void  renderLoop();
			void  stepLoop();
			void  Render(void);

			static Engine*				_instance;
			int							_windowHeight;
			int							_windowWidth;
			int							_objectUniqueID;
			bool						_closeWindow;
			std::string					_windowName;
			Camera2D*					_2DCamera;

		public:
			void set2DCamera(Camera2D& camera);
			void Remove2DCamera(void);
			void loadTextureImage();
			static Engine& getInstance();
			static void initInstance(std::string windowName, int windowHeight, int windowWidth);
			void loop(void (*func)(Engine &));
			void closeWindow();
			int addObject(Object& object, bool render);
			SpriteMap 					sprites;
			TexturePath 				textures;
			std::vector<Object>			objectList;
			std::vector<Object*>		renderList;
			std::vector<Object*>		uiRenderList;
	};

#endif