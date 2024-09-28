#include "../include/Engine.h"

void  Engine::set2DCamera(Camera2D& camera) { this->_2DCamera = &camera; }

void  Engine::Remove2DCamera(void) { this->_2DCamera = NULL; }


static Rectangle CalculateViewPort(Camera2D* camera) {
	if (!camera)
		return Rectangle{0,0,0,0};
	const float height = GetScreenHeight() /  1 ;// camera->zoom; //
	const float width = GetScreenWidth()   /  1 ;// camera->zoom; //
	const Rectangle ViewPort = Rectangle {
		camera->target.x - (width / 2.0f),
		camera->target.y - (height / 2.0f),
		width,
		height
	};
	return ViewPort;
}

void Engine::render(void) {
	const Rectangle ViewPort = CalculateViewPort(this->_2DCamera);
	///
	if (this->_2DCamera) { BeginMode2D(*this->_2DCamera); } //! look for cam
	for (size_t i = 0; i < renderList.size(); i++) {
		if (renderList[i] && renderList[i]->texture) {
			const Object& tmp = *renderList[i];
			DrawTextureEx(*tmp.texture, tmp.position, 0, 1, WHITE);
		}
	}
	if (this->_2DCamera) { EndMode2D(); } //! end 2Dmode
	///
	for (size_t i = 0; i < uiRenderList.size(); i++) {
		if (uiRenderList[i] && uiRenderList[i]->texture) {
			const Object& tmp = *uiRenderList[i];
			DrawTextureEx(*tmp.texture, tmp.position, 0, 1, WHITE);
		}
	}
}