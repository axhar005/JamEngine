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
		{"fireball", {"asset/fireball.png"}}
	};
}

void initObject(Engine& e)
{
	Fireball f({0, 0}, e.sprites["fireball"]);

	e.addObject(f, true);
}

int main()
{
	Engine e("ENGINE", 300, 400);
	initTexture(e);
	initObject(e);
	e.loop(mainLoop);
	return 0;
}
