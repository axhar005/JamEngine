#include "../include/Engine.h"
#include "../include/Fireball.h"

void mainLoop(Engine& e)
{
	// your gameplay
	static float zoom = 1;
	const float zoomJump = 0.05;
	const int  cameraSpeed = 10 / zoom;
	if (IsKeyPressed(KEY_P)) { e.closeWindow(); }
	if (IsKeyDown(KEY_W)) { e.objectList[e.objectList.size() -1]->position.y += -cameraSpeed; }
	if (IsKeyDown(KEY_S)) { e.objectList[e.objectList.size() -1]->position.y +=  cameraSpeed; }
	if (IsKeyDown(KEY_A)) { e.objectList[e.objectList.size() -1]->position.x += -cameraSpeed; }
	if (IsKeyDown(KEY_D)) { e.objectList[e.objectList.size() -1]->position.x +=  cameraSpeed; }
	if (IsKeyPressed(KEY_UP) && zoom + zoomJump <= 4)   {zoom += zoomJump; }
	if (IsKeyPressed(KEY_DOWN) && zoom - zoomJump >= 0) {zoom -= zoomJump; }
	e.set2DCameraZoom(zoom);
	e.set2DCameraPotions(e.objectList[e.objectList.size() -1], true);
	for (size_t i = 0; i < e.objectList.size() - 1; i++) {
		float a = (i % 2 == 0) ? 0.05 : -0.05;
		e.objectList[i]->position.x +=  a;
		e.objectList[i]->position.y += -a;
	}
	
}

void initTexture(Engine& e)
{
	e.textures = {
		{"fireball", {"asset/no_texture.png"}},
		{"dev", {"asset/test.png"}},
		// {"player_down", {"asset/player/player_down_0.png", "asset/player/player_down_1.png"}},
	};
	e.loadTextureImage();
}

void initObject(Engine& e)
{
	int tmp = 0;
	const int id = e.addObject(new Object({0,0},e.sprites["dev"]), true);
	e.objectList[0]->hitbox.box.height = 20;
	e.objectList[0]->hitbox.box.width = 20;
	for (int j = 0; j < 200; j++) {
		for (int i = 0; i < 200; i++) {
			e.addObject(new Fireball({float(16 * j), float(16 * i)}, e.sprites["fireball"]), true);
			Object* tmpobj = e.getObjectByID(tmp);
			tmpobj->layer = 1;
		}
	}
	Object* player = e.getObjectByID(id);
	player->layer = 4;
	e.sortLayer();
}

int main()
{
	Engine::initInstance(1280, 720, "ENGINE");
	Engine& e = Engine::getInstance();
	initTexture(e);
	initObject(e);
	Camera2D cam = {{0,0}, {0,0}, 0, 1};
	e.set2DCamera(cam);
	e.loop(mainLoop);
	return 0;
}
