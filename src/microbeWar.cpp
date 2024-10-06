#include "../include/Engine.h"
#include "../include/Microbe.h"
#include "../include/PetriDish.h"
#include <cmath>
/*
void mainLoop(Engine& e)
{
	static float zoom = 1;
	const float zoomJump = 0.1;

	if (IsKeyDown(KEY_UP))		{zoom += zoomJump; zoom = fmin(zoom, 7.0f);}
	if (IsKeyDown(KEY_DOWN))	{zoom -= zoomJump; zoom = fmax(zoom, 0.2f);}

	e.set2DCameraZoom(zoom);
	e.set2DCameraPotions(e.renderList[e.renderList.size() -1], true);

	e.sortLayer();
}

void initTexture(Engine& e)
{
	e.textures = {
		//{"dev", {"asset/test.png"}},
		{"PetriDish",{"asset/PetriDish.png"}},
		{"Player",{"asset/PlayerCell.png"}},
		{"Nutrient", {"asset/Nutrient.png"}},
		{"Microbe_1",{"asset/Cell_1.png"}},
		{"Microbe_2",{"asset/Cell_2.png"}},
		{"Microbe_3",{"asset/Cell_3.png"}},
	};
	e.loadTextureImage();
}

void initAudio(Engine& e) {
	e.importSound("audio/untitled.wav");
}

void initObject(Engine& e)
{
	PetriDish* petriDish = new PetriDish({0,0}, e.sprites["PetriDish"], 1000);

	petriDish->spawnNutrient(e.sprites["Nutrient"], 100);
	petriDish->spawnMicrobe("BadGuys", e.sprites["Microbe_2"], 10);
	petriDish->spawnMicrobe("GoodGuys", e.sprites["Microbe_1"], 9);
	petriDish->spawnPlayer("GoodGuys", e.sprites["Player"]);

	e.sortLayer();
}


int main()
{
	Engine& e = Engine::initInstance(1280, 720, "MicrobeWar");
	initTexture(e);
	initAudio(e);
	initObject(e);
	Camera2D cam = {{0,0}, {0,0}, 0, 1};
	e.set2DCamera(cam);
	e.loop(mainLoop);
	return 0;
}
*/