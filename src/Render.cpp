#include "../include/Engine.h"

void  Engine::set2DCamera(Camera2D& camera) { this->_2DCamera = &camera; }
void  Engine::set2DCameraZoom(float zoom) { if (this->_2DCamera) { this->_2DCamera->zoom = zoom; } }

//this whill not free the pointer
void  Engine::Remove2DCamera(void) { this->_2DCamera = NULL; }


static Rectangle CalculateViewPort(Camera2D* camera) {
	if (!camera)
		return Rectangle{0,0,0,0};
	const float newZoom = 1 / camera->zoom;
	const float height = (GetScreenHeight());
	const float width  = (GetScreenWidth() );
	const Rectangle ViewPort = Rectangle {
		camera->target.x, camera->target.y,
		width * newZoom, height * newZoom
	};
	return ViewPort;
}

void Engine::render(void) {
	const Rectangle ViewPort = CalculateViewPort(this->_2DCamera);
	///
	static  unsigned char t = 70;
	const Color box = {255, 0, 0, t++};
	const Color boxPort = {0, 0, 255, 25};
	if (this->_2DCamera) { BeginMode2D(*this->_2DCamera); } //? look for cam
	for (size_t i = 0; i < renderList.size(); i++) {
		if (renderList[i] && renderList[i]->texture) {
			Object& tmp = *renderList[i]; //!! put back const after test
			tmp.hitbox.x = tmp.position.x;
			tmp.hitbox.y = tmp.position.y;
			tmp.hitbox.height = 16;
			tmp.hitbox.width = 16;
			if (!this->_2DCamera || CheckCollisionRecs(ViewPort, tmp.hitbox)) {
				DrawTextureEx(*tmp.texture, tmp.position, 0, 1, WHITE);
				DrawRectangleRec(tmp.hitbox, box);
				DrawText("in", 4,0, 40, BLACK);
			}
			else
				DrawText("out", 4,0, 40, BLACK);
		}
	}
	DrawRectangleRec(ViewPort, boxPort);
	if (this->_2DCamera) { EndMode2D(); } //? end 2Dmode
	///
	for (size_t i = 0; i < uiRenderList.size(); i++) {
		if (uiRenderList[i] && uiRenderList[i]->texture) {
			const Object& tmp = *uiRenderList[i];
			DrawTextureEx(*tmp.texture, tmp.position, 0, 1, WHITE);
		}
	}
}