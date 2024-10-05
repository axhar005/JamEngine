#include "../include/Engine.h"
#include "../include/Fireball.h"

int		tid;
int		trigerid;
int		playerid;

void mainLoop(Engine& e)
{
	// your gameplay
	Object* playerPtr = e.getObjectByID(playerid);
	static float zoom = 1;
	const float zoomJump = 0.1;
	const int  cameraSpeed = 5 / (zoom / 2);
	static bool showTrigger = false;
	if (IsKeyPressed(KEY_P)) { e.closeWindow(); }
	if (playerPtr) {
		if (IsKeyDown(KEY_W)) { playerPtr->position.y += -cameraSpeed; }
		if (IsKeyDown(KEY_S)) { playerPtr->position.y +=  cameraSpeed; }
		if (IsKeyDown(KEY_A)) { playerPtr->position.x += -cameraSpeed; }
		if (IsKeyDown(KEY_D)) { playerPtr->position.x +=  cameraSpeed; }
	}
	if (IsKeyPressed(KEY_T)) {e.playSound("untitled.wav"); }
	if (IsKeyDown(KEY_UP)   && zoom + zoomJump <= 7) {zoom += zoomJump; }
	if (IsKeyDown(KEY_DOWN) && zoom - zoomJump > 0.1)  {zoom -= zoomJump; }
	e.set2DCameraZoom(zoom);
	e.set2DCameraPotions(e.renderList[e.renderList.size() -1], true);
	if (IsKeyPressed(KEY_O)) {
		showTrigger = !showTrigger;
		for(size_t i = 0; i < e.triggerList.size(); i++) {
		e.triggerList[i]->drawTrigger = showTrigger;
	}
	}
	for (size_t i = 1; i < e.renderList.size() - 2; i++) {
		float a = (i % 2 == 0) ? 0.05 : -0.05;
		e.renderList[i]->position.x +=  +a;
		e.renderList[i]->position.y +=  -a;
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

void initAudio(Engine& e) {
	
}

void initObject(Engine& e)
{
	playerid = e.addObject(new Object({0,0},e.sprites["dev"]), true);
	e.objectList[0]->hitbox.box.height = 20;
	e.objectList[0]->hitbox.box.width = 20;
	trigerid = e.addObject(new Trigger({0,0,}), false);
	e.triggerList.push_back((Trigger *)e.getObjectByID(trigerid));
	Trigger* triggerObj = (Trigger*)e.getObjectByID(trigerid);
	for (int j = 0; j < 200; j++) {
		for (int i = 0; i < 200; i++) {
			int a = e.addObject(new Fireball({float(16 * j), float(16 * i)}, e.sprites["fireball"]), true);
			Object* tmpobj = e.getObjectByID(a);
			tmpobj->layer = 1;
			tmpobj->setName("X");
		}
	}
	Object* player = e.getObjectByID(playerid);
	triggerObj->add(player);
	player->layer = 4;
	player->setName("dev");
	e.sortLayer();
	e.importSound("audio/untitled.wav");
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
