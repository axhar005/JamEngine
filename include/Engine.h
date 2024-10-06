#ifndef ENGINE_H
# define ENGINE_H
	#include "engineSetup.h"
	#include "Object.h"
	#include "Trigger.h"

class Engine
{
		private:
			Engine(int windowWidth, int windowHeight, std::string windowName);
			~Engine();
			Engine(const Engine&) = delete;
			Engine(Engine&&) = delete;
			Engine& operator=(const Engine&) = delete;
			Engine& operator=(Engine&&) = delete;
			void unloadTextureImage();
			void renderLoop();
			void stepLoop();
			void drawLoop();
			void render(void);
			void removeAll();
			static Engine*				_instance;
			int							_windowHeight;
			int							_windowWidth;
			int							_objectUniqueID;
			bool						_closeWindow;
			std::string					_windowName;
			Camera2D*					_2DCamera;

		public:
			// Camera
			void set2DCameraPotions(Vector2 pos);
			void set2DCameraPotions(Object* obj, bool center);

			void set2DCameraZoom(float zoom);

			void set2DCamera(Camera2D& camera);
			void Remove2DCamera(void);

			void sortLayer(void);

			void loadTextureImage();
			static Engine& getInstance();
			static Engine& initInstance(int windowWidth, int windowHeight, std::string windowName);
			void loop(void (*func)(Engine &));
			void closeWindow();

			Object* getObjectByID(int id);
			int addObject(Object* object);
			int addObject(Trigger* trigger);
			bool addObjectToRender(Object* object);
			bool addObjectToRenderByID(int id);

			bool removeObject(Object* obj);
			bool removeObjectByID(int id);
			bool removeObjectFromRender(Object* object);
			bool removeObjectFromRenderByID(int id);

			SpriteMap 					sprites;
			TexturePath 				textures;
			std::vector<Object*>		objectList;
			std::vector<Object*>		renderList;
			std::vector<Object*>		uiRenderList;
			std::vector<Trigger*>		triggerList;
			//
			float						volume;
			void	importSound(const char* name);
			void	removeAllSound(void);
			void	playSound(const char* name);
			std::map<std::string, Sound>		soundMap;
};

#endif