#include "../include/Engine.h"

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
		{"player_down", {"asset/player/player_down_0.png", "asset/player/player_down_1.png"}},
		{"fireball", {"asset/Spell/FireBall.png"}}
	};
}

int main()
{
	Engine e("ENGINE", 300, 400);
	initTexture(e);
	e.loop(mainLoop);
	return 0;
}