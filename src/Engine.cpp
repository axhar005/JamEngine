#include "../include/Engine.h"
Engine* Engine::_instance = nullptr;

Engine::Engine(int windowWidth, int windowHeight, std::string windowName)
{
	objectList.reserve(VECTOR_RESERVE);
	renderList.reserve(VECTOR_RESERVE);
	uiRenderList.reserve(VECTOR_RESERVE);
	_windowWidth = windowWidth;
	_windowHeight = windowHeight;
	_windowName = windowName;
	_objectUniqueID = 0;
	_closeWindow = false;
	InitWindow(_windowWidth, _windowHeight, _windowName.c_str());
}

Engine::~Engine()
{
	unloadTextureImage();
	CloseWindow();
	removeAll();
}

void Engine::initInstance(int windowWidth, int windowHeight, std::string windowName) {
		if (_instance == nullptr) {
			_instance = new Engine(windowWidth, windowHeight, windowName);
		} else {
			throw std::runtime_error("Instance alrady initialized.");
		}
	}

Engine& Engine::getInstance()
{
	if (_instance == nullptr) {
		throw std::runtime_error("Instance none initialized.");
	}
	return *_instance;
}

void Engine::loadTextureImage()
{
	for (const auto &item : textures)
	{
		const std::string &key = item.first;
		const std::vector<std::string> &paths = item.second;

		std::vector<SpriteFrame> spriteList;
		spriteList.reserve(paths.size());
		for (const std::string &path : paths)
		{
			SpriteFrame s;
			s.image = LoadImage(path.c_str());
			if (s.image.data == nullptr)
			{
				TraceLog(LOG_WARNING, "Unable to load image : %s", path.c_str());
				continue;
			}
			s.texture = LoadTextureFromImage(s.image);
			spriteList.push_back(s);
		}
		sprites[key] = spriteList;
	}
}

void Engine::unloadTextureImage()
{
	for (auto &item : sprites)
	{
		for (auto &s : item.second)
		{
			UnloadTexture(s.texture);
			UnloadImage(s.image);
		}
	}
}

void Engine::stepLoop()
{
	for (auto &&i : objectList)
	{
		i->step();
	}
}

int Engine::addObject(Object* object, bool render)
{
	if (object == NULL)
		return -1;
	for (auto &&obj : objectList)
	{
		if(obj == object){
			return -1;
		}
	}
	object->id = _objectUniqueID++;
	objectList.push_back(object);
	if (render)
		renderList.push_back(object);
	return _objectUniqueID;
}

Object* Engine::getObjectByID(int id)
{
	for (auto &&obj : objectList)
	{
		if(obj->id == id){ return obj; }
	}
	return NULL;
}

bool Engine::removeObjectByID(int id)
{
	for (auto it = objectList.begin(); it != objectList.end(); ) {
		if ((*it)->id == id){
			for (auto itt = renderList.begin(); itt != renderList.end(); ) {
				if ((*itt)->id == id){
					renderList.erase(itt);
				}
				break;
			}
			for (auto itt = uiRenderList.begin(); itt != uiRenderList.end(); ) {
				if ((*itt)->id == id){
					uiRenderList.erase(itt);
				}
				break;
			}
			delete *it;
			objectList.erase(it);
			return true;
		}
	}
	return false;
}

void Engine::removeAll()
{
	for (auto it = objectList.begin(); it != objectList.end(); ) {
		delete *it;
	}
	renderList.clear();
	uiRenderList.clear();
	objectList.clear();
}

void Engine::renderLoop()
{
	for (auto &&obj : renderList)
	{
		DrawTexture(*obj->texture, obj->position.x, obj->position.y, WHITE);
	}
}

void Engine::loop(void (*func)(Engine &))
{
	SetTargetFPS(60);
	SetExitKey(KEY_ESCAPE);
	std::cout << "ici1" << std::endl;

	while (!WindowShouldClose() && !_closeWindow)
	{
	std::cout << "ici2" << std::endl;

		func(*this);
		stepLoop();
		BeginDrawing();
			ClearBackground(RAYWHITE);
			DrawGrid(20, 10.0f);
			render();
		EndDrawing();
	}
}

void Engine::closeWindow()
{
	_closeWindow = true;
}