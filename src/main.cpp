#include "../include/Engine.h"
#include "../include/Fireball.h"
#include "../include/Player.h"

Player* player;
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
	e.set2DCameraPotions(player, true);
	if (IsKeyPressed(KEY_O)) {
		showTrigger = !showTrigger;
		for(size_t i = 0; i < e.triggerList.size(); i++) {
		e.triggerList[i]->drawTrigger = showTrigger;
	}
	}
	for (size_t i = 1; i < e.renderList.size() - 1; i++) {
		float a = (i % 2 == 0) ? 0.05 : -0.05;
		e.renderList[i]->position.x +=  +a;
		e.renderList[i]->position.y +=  -a;
	}
	if (CheckCollisionEllipseRecs(player->hitbox.box, e.objectList[2]->hitbox.box)){
		player->showHitbox = true;
	}else{
		player->showHitbox = false;
	}
	e.sortLayer();
}

void initTexture(Engine& e)
{
	e.initTexture({
		{"fireball", {"asset/no_texture.png"}},
		{"dev", {"asset/test.png"}},
		{"dev_2", {"asset/16x32_test.png"}},
		// {"player_down", {"asset/player/player_down_0.png", "asset/player/player_down_1.png"}},
	});
}

void initAudio(Engine& e) {

}

void initObject(Engine& e)
{
	player = new Player({0,0}, e.getSprite("dev"), true);
	playerid = player->id;
	Trigger* tt = new Trigger({0,0,}, {10, 10});
	trigerid = tt->id;
	Trigger* triggerObj = (Trigger*)e.getObjectByID(trigerid);
	for (int j = 0; j < 200; j++) {
		for (int i = 0; i < 200; i++) {
			Object* tmpobj = new Fireball({float(16 * j), float(16 * i)}, e.getSprite("fireball"), true, 1);
			// tmpobj->setLayer(1);
			tmpobj->setName("X");
		}
	}
	triggerObj->add(player);
	player->setLayer(4);
	player->setName("dev");
	e.sortLayer();
	// e.importSound("audio/untitled.wav");
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
