#include "../include/Engine.h"

void  Engine::set2DCamera(Camera2D& camera) { this->_2DCamera = &camera; }
void  Engine::set2DCameraZoom(float zoom) { if (this->_2DCamera) { this->_2DCamera->zoom = zoom; } }

void  Engine::set2DCameraPotions(Object* obj, bool center = true) {
	if (this->_2DCamera && obj) {
		Vector2 tmp = obj->position;
		if (center) {
			tmp.x += obj->hitbox.width / 2;
			tmp.y += obj->hitbox.height / 2;
		}
		this->set2DCameraPotions(tmp);
	}
}

void  Engine::set2DCameraPotions(Vector2 pose) { 
	if (this->_2DCamera) {
		pose.x -= float(GetScreenWidth() / 2)  / this->_2DCamera->zoom;
		pose.y -= float(GetScreenHeight() / 2) / this->_2DCamera->zoom;
		this->_2DCamera->target = pose;
	}
}

//this whill not free the pointer
void  Engine::Remove2DCamera(void) { this->_2DCamera = NULL; }


static Rectangle CalculateViewPort(Camera2D* camera) {
	if (!camera)
		return Rectangle{0,0,0,0};
	const float height = (GetScreenHeight());
	const float width  = (GetScreenWidth());
	const Rectangle ViewPort = Rectangle {
		camera->target.x, camera->target.y,
		width / camera->zoom, height / camera->zoom };
	return ViewPort;
}

#define drawId 0

void Engine::render(void) {
	const Rectangle ViewPort = CalculateViewPort(this->_2DCamera);
	const Color box = {255, 0, 0, 70};
	unsigned int hits = 0;
	///
	if (this->_2DCamera) { BeginMode2D(*this->_2DCamera); } //? look for cam
	for (size_t i = 0; i < renderList.size(); i++) {
		if (renderList[i] && renderList[i]->texture) {
			Object& tmp = *renderList[i]; //!! put back const after test
			if (!this->_2DCamera || CheckCollisionRecs(ViewPort, tmp.hitbox)) {
				
				#if (drawId)
					char sdev[50];
					sprintf(sdev, "%li %u", i, tmp.layer);
				#endif
				DrawTextureEx(*tmp.texture, tmp.position, 0, 1, WHITE);
				//DrawRectangleRec(tmp.hitbox, box);
				#if (drawId)
					DrawText(sdev, tmp.position.x, tmp.position.y, 5, BLUE);
				#endif
				hits++;
			}
		}
	}
	if (this->_2DCamera) { EndMode2D(); } //? end 2Dmode
	///
	char s[50];
	sprintf(s, "totals hits = %u", hits);
	DrawText(s, 4,20, 30, BLUE);
	DrawFPS(0,0);
	for (size_t i = 0; i < uiRenderList.size(); i++) {
		if (uiRenderList[i] && uiRenderList[i]->texture) {
			const Object& tmp = *uiRenderList[i];
			DrawTextureEx(*tmp.texture, tmp.position, 0, 1, WHITE);
		}
	}
}