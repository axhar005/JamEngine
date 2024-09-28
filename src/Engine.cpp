#include "../include/Engine.h"
Engine* Engine::_instance = nullptr;

Engine::Engine(std::string windowName, int windowHeight, int windowWidth)
{
	_windowName = windowName;
	_windowHeight = windowHeight;
	_windowWidth = windowWidth;
	_objectUniqueID = 0;
	_closeWindow = false;
	InitWindow(_windowWidth, _windowHeight, _windowName.c_str());
}

Engine::~Engine()
{
	unloadTextureImage();
	CloseWindow();
}

void Engine::initInstance(std::string windowName, int windowHeight, int windowWidth) {
		if (_instance == nullptr) {
			_instance = new Engine(windowName, windowHeight, windowWidth);
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
		i.step();
	}
}

int Engine::addObject(Object &object, bool render)
{
	for (auto &&obj : objectList)
	{
		if(&obj == &object){
			return -1;
		}
	}
	object.id = _objectUniqueID++;
	objectList.push_back(object);
	if (render)
		renderList.push_back(&object);
	return _objectUniqueID;
}

void Engine::renderLoop()
{
	for (auto &&obj : renderList)
	{
		// DrawTexture(*obj->texture, obj->position.x, obj->position.y, WHITE);
	}
}

void Engine::loop(void (*func)(Engine &))
{
	SetTargetFPS(60);
	SetExitKey(0);
	while (!WindowShouldClose() && !_closeWindow)
	{
		func(*this);
		stepLoop();
		BeginDrawing();
			ClearBackground(RAYWHITE);
			DrawGrid(20, 10.0f);

			renderLoop(); /* render */
		EndDrawing();
	}
}

void Engine::closeWindow()
{
	_closeWindow = true;
}