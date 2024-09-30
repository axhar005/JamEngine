#include "../include/Engine.h"
#include "../include/Fireball.h"

void mainLoop(Engine& e)
{
	// your gameplay
	if (IsKeyPressed(KEY_P))
	{
		e.closeWindow();
	}
	if (IsKeyDown(KEY_W)) { e.objectList[0]->position.y--; }
	if (IsKeyDown(KEY_S)) { e.objectList[0]->position.y++; }
	if (IsKeyDown(KEY_A)) { e.objectList[0]->position.x--; }
	if (IsKeyDown(KEY_D)) { e.objectList[0]->position.x++; }
	static float zoom = 1;
	const float zoomJump = 0.1;
	if (IsKeyPressed(KEY_UP) && zoom + zoomJump <= 4)   {zoom += zoomJump; }
	if (IsKeyPressed(KEY_DOWN) && zoom - zoomJump >= 0) {zoom -= zoomJump; }
	e.set2DCameraZoom(zoom);
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
	Camera2D cam = {{0,0}, {0,0}, 0, 1};
	e.set2DCamera(cam);
	e.loop(mainLoop);
	return 0;
}
