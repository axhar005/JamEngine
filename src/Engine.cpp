#include "../include/Engine.h"
Engine* Engine::_instance = nullptr;

Engine::Engine(int windowWidth, int windowHeight, std::string windowName)
{
	objectList.reserve(VECTOR_RESERVE);
	renderList.reserve(VECTOR_RESERVE);
	uiRenderList.reserve(VECTOR_RESERVE);
	triggerList.reserve(VECTOR_RESERVE);
	_windowWidth = windowWidth;
	_windowHeight = windowHeight;
	_windowName = windowName;
	_objectUniqueID = 0;
	_closeWindow = false;
	_2DCamera = NULL;
	InitWindow(_windowWidth, _windowHeight, _windowName.c_str());
	//sound <---
	InitAudioDevice();
	SetMasterVolume(1);
}

Engine::~Engine()
{
	removeAllSound();
	CloseAudioDevice();
	// ^---
	unloadTextureImage();
	CloseWindow();
	removeAll();
}

Engine& Engine::initInstance(int windowWidth, int windowHeight, std::string windowName) {
	if (_instance == nullptr) {
		_instance = new Engine(windowWidth, windowHeight, windowName);
	} else {
		throw std::runtime_error("Instance alrady initialized.");
	}
	return *_instance;
}

Engine& Engine::getInstance()
{
	if (_instance == nullptr) {
		throw std::runtime_error("Instance none initialized.");
	}
	return *_instance;
}

void Engine::closeWindow()
{
	_closeWindow = true;
}

void Engine::loadTextureImage()
{
	for (const auto &item : _textures)
	{
		const std::string &key = item.first;
		const std::vector<std::string>& paths = item.second;

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
		spriteMap[key] = spriteList;
	}
}

void Engine::unloadTextureImage()
{
	for (auto &item : spriteMap)
	{
		for (auto &s : item.second)
		{
			UnloadTexture(s.texture);
			UnloadImage(s.image);
		}
	}
}

void Engine::initTexture(TexturePath textures)
{
	_textures = textures;
	loadTextureImage();
}

Sprite Engine::getSprite(std::string name)
{
	SpriteMap::iterator it = spriteMap.find(name);

	if (it != spriteMap.end()) {
		return it->second;
	} else {
		throw std::runtime_error("The sprite '" + name + "' was not found in the SpriteMap.");
	}
}

static bool  lookLayer(Object* a, Object* b) {
	return (a->layer < b->layer);
}

void Engine::sortLayer(void) {
	std::stable_sort(renderList.begin(), renderList.end(), lookLayer);
}

void Engine::stepLoop()
{
	for (auto &&i : objectList)
	{
		i->update();
		i->step();
	}
}

void Engine::drawLoop()
{
	for (auto &&i : objectList)
	{
		i->draw();
	}
}

Object* Engine::getObjectByID(int id)
{
	for (auto &&obj : objectList)
	{
		if(obj->id == id){ return obj; }
	}
	return NULL;
}

int Engine::addObject(Object* object)
{
	if (object == NULL)
		return -1;
	for (auto &&obj : objectList)
	{
		if(obj == object){
			return -1;
		}
	}
	object->id = _objectUniqueID;
	objectList.push_back(object);
	return _objectUniqueID++;
}

int Engine::addTrigger(Trigger* trigger)
{
	if (trigger == NULL)
		return -1;
	for (auto &&obj : triggerList)
	{
		if(obj == trigger){
			return -1;
		}
	}
	trigger->id = _objectUniqueID;
	triggerList.push_back(trigger);
	return _objectUniqueID++;
}

bool Engine::addObjectToRender(Object* object)
{
	if (!object)
		return false;
	for (auto &&obj : renderList)
	{
		if(obj == object){
			return false;
		}
	}
	renderList.push_back(object);
	// sortLayer();
	return true;
}

bool Engine::addObjectToRenderByID(int id)
{
	for (auto &&obj : renderList)
	{
		if(obj->id == id){
			return false;
		}
	}
	Object* tmp = getObjectByID(id);
	if (tmp)
	{
		renderList.push_back(tmp);
		// sortLayer();
		return true;
	}
	return false;
}

bool Engine::removeObjectFromRender(Object* object)
{
	if (!object)
		return false;
	for (auto it = renderList.begin(); it != renderList.end(); )
	{
		if (*it == object)
		{
			it = renderList.erase(it);
			return true;
		}
		else
			++it;
	}
	return false;
}

bool Engine::removeObjectFromRenderByID(int id)
{
	for (auto it = renderList.begin(); it != renderList.end(); )
	{
		if ((*it)->id == id)
		{
			it = renderList.erase(it);
			return true;
		}
		else
			++it;
	}
	return false;
}

bool Engine::removeObjectByID(int id)
{
	for (auto it = objectList.begin(); it != objectList.end(); )
	{
		if ((*it)->id == id)
		{
			renderList.erase(std::remove(renderList.begin(), renderList.end(), *it), renderList.end());
			uiRenderList.erase(std::remove(uiRenderList.begin(), uiRenderList.end(), *it), uiRenderList.end());
			triggerList.erase(std::remove(triggerList.begin(), triggerList.end(), *it), triggerList.end());
			it = objectList.erase(it);
			return true;
		}
		else
			++it;
	}
	return false;
			printf("delete object\n");
}

bool Engine::removeObject(Object* object)
{
	if (!object)
		return false;
	for (auto it = objectList.begin(); it != objectList.end(); it++)
	{
		if (*it == object)
		{
			renderList.erase(std::remove(renderList.begin(), renderList.end(), object), renderList.end());
			uiRenderList.erase(std::remove(uiRenderList.begin(), uiRenderList.end(), object), uiRenderList.end());
			triggerList.erase(std::remove(triggerList.begin(), triggerList.end(), object), triggerList.end());
			it = objectList.erase(it);
			return true;
		}
		else
			++it;
	}
	return false;
}

void Engine::removeAll()
{
	renderList.clear();
	uiRenderList.clear();
	triggerList.clear();
	for (auto it = objectList.begin(); it != objectList.end(); ++it) {
		delete *it;
	}
	objectList.clear();
}

void Engine::renderLoop()
{
	for (auto &&obj : renderList)
	{
		DrawTexture(*obj->texture, obj->position.x, obj->position.y, WHITE);
	}
}

void Engine::importSound(const char* name)
{
	std::string tmpname;
	if (!name)
		return;
	const char* tmp = strrchr(name, '/');
	if (!tmp)
		return ;
	tmpname = tmp[0] == '/' ? tmp + 1 : tmp;
	if (soundMap.find(tmpname) == soundMap.end()) {
		Sound s = LoadSound(name);
		std::cout << tmpname << std::endl;
		soundMap[tmpname] = s;
	}
	else {
		std::cerr << name << " is all ready in map" << std::endl;
	}
}

void Engine::removeAllSound(void)
{
	for (std::map<std::string, Sound>::iterator it = this->soundMap.begin();
	it != this->soundMap.end(); it++) {
		Sound tmp = (*it).second;
		UnloadSound(tmp);
	}
}

void Engine::playSound(const char* name)
{
	if (!name)
		return ;
	if (soundMap.find(name) != soundMap.end()) {
		if (IsSoundReady(soundMap[name]))
			PlaySound(soundMap[name]);
	}
}


void Engine::loop(void (*func)(Engine &))
{
	SetTargetFPS(60);
	SetExitKey(KEY_ESCAPE);

	const float targetFrameTime = 1.0f / 60.0f;
	float accumulatedTime = 0.0f;

	while (!WindowShouldClose() && !_closeWindow)
	{
		float deltaTime = GetFrameTime();
		accumulatedTime += deltaTime;

		while (accumulatedTime >= targetFrameTime)
		{
			func(*this);
			stepLoop();
			accumulatedTime -= targetFrameTime;
		}
		BeginDrawing();
		{
			ClearBackground(BCKG_COLOR);
			DrawGrid(20, 10.0f);
			render();
		}
		EndDrawing();
	}
}
