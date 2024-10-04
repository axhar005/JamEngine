#include "../include/Engine.h"
#include "../include/Fireball.h"

void mainLoop(Engine& e)
{
	// your gameplay
	if (IsKeyPressed(KEY_P))
	{
		e.closeWindow();
	}
}

void initTexture(Engine& e)
{
	e.textures = {
		{"fireball", {"asset/no_texture.png"}},
		// {"player_down", {"asset/player/player_down_0.png", "asset/player/player_down_1.png"}},
	};
	e.loadTextureImage();
}

void initObject(Engine& e)
{
	e.addObject(new Fireball({100, 100}, e.sprites["fireball"]), true);
}

int main()
{
	Engine::initInstance(1280, 720, "ENGINE");
	Engine& e = Engine::getInstance();
	initTexture(e);
	initObject(e);
	e.loop(mainLoop);
	return 0;
}
