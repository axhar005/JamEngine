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
		// {"player_down", {"asset/player/player_down_0.png", "asset/player/player_down_1.png"}},
		{"fireball", {"asset/FireBall.png"}}
	};
	e.loadTextureImage();
}

void initObject(Engine& e)
{
	Fireball f({0, 0}, e.sprites["fireball"]);
}

int main()
{
	Engine::initInstance("ENGINE", 500, 600);
	Engine& e = Engine::getInstance();
	initTexture(e);
	initObject(e);
	e.loop(mainLoop);
	return 0;
}
