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
		{"fireball", {"asset/Fireball.png"}},
		// {"player_down", {"asset/player/player_down_0.png", "asset/player/player_down_1.png"}},
	};
	e.loadTextureImage();
}

void initObject(Engine& e)
{
	new Fireball({100, 100}, e.sprites["fireball"]);
}

int main()
{
	Engine::initInstance(640, 480, "ENGINE");
	Engine& e = Engine::getInstance();
	initTexture(e);
	initObject(e);
	e.loop(mainLoop);
	return 0;
}
