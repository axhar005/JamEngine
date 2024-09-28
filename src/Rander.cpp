#include "../include/Engine.h"

void  Engine::set2DCamera(Camera2D& camera) { this->_2DCamera = &camera; }

void  Engine::Remove2DCamera(void) { this->_2DCamera = NULL; }


static Rectangle CalculateViewPort(Camera2D* camera) {
	if (!camera)
		return Rectangle{0,0,0,0};
	const float height = GetScreenHeight() / camera->zoom;
	const float width = GetScreenWidth() / camera->zoom;
	const Rectangle ViewPort = Rectangle {
		camera->target.x - (width / 2.0f),
		camera->target.y - (height / 2.0f),
		width,
		height
	};
	return ViewPort;
}

void Engine::Rander(void) {
	const Rectangle ViewPort = CalculateViewPort(this->camera);
	
}