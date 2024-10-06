#include "../include/Engine.h"

void  Engine::set2DCamera(Camera2D& camera) { this->_2DCamera = &camera; }
void  Engine::set2DCameraZoom(float zoom) { if (this->_2DCamera) { this->_2DCamera->zoom = zoom; } }

void  Engine::set2DCameraPosition(Object* obj, bool center = true) {
	if (this->_2DCamera && obj) {
		Vector2 tmp = obj->position;
		if (center) {
			tmp.x += obj->hitbox.box.width / 2;
			tmp.y += obj->hitbox.box.height / 2;
		}
		this->set2DCameraPosition(tmp);
	}
}

void  Engine::set2DCameraPosition(Vector2 pose) {
	if (this->_2DCamera) {
		pose.x -= float((float)GetScreenWidth() / 2)  / this->_2DCamera->zoom;
		pose.y -= float((float)GetScreenHeight() / 2) / this->_2DCamera->zoom;
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

#define drawId      true
#define drawTrigger false

void Engine::render(void) {
	const Rectangle ViewPort = CalculateViewPort(this->_2DCamera);
	const Color box = {255, 10, 0, 70};
	unsigned int hits = 0;
	///
	if (this->_2DCamera) { BeginMode2D(*this->_2DCamera); } //? look for cam
	for (size_t i = 0; i < renderList.size(); i++) {
		if (renderList[i] && renderList[i]->texture) {
			Object& tmp = *renderList[i]; //!! put back const after test
			if (!this->_2DCamera || CheckCollisionRecs(ViewPort, tmp.hitbox.box)) {
				#if (drawId)
				char sdev[80];
				bzero(sdev, 80);
				const char *name = tmp.getName().c_str();
				sprintf(sdev, "%li %u\n%s", i, tmp.layer, name);
				#endif
				DrawTextureEx(*tmp.texture, tmp.position, tmp.rotation, 1, WHITE);
				// DrawRectangleRec(tmp.hitbox.box, box);
				#if (drawId)
				DrawText(sdev, tmp.position.x - 1, tmp.position.y -1, 8, BLACK);
				DrawText(sdev, tmp.position.x, tmp.position.y, 8, WHITE);
				#endif
				tmp.draw();
				hits++;
			}
		}
	}
	for (size_t i = 0; i < this->triggerList.size(); i++) {
		if (triggerList[i]) {
			Trigger* tmp = triggerList[i];
			#if (drawTrigger)
			tmp->draw();
			#endif
			// if you want to see that the zone were the box overlap
			const std::vector<int> list = tmp->hit();
			std::cout << list.size() << "\n";
			if (list.size()) {
				Mouse.draw = true;
				Mouse.drawWindow();
			}
			else
				Mouse.draw = false;
		}
	}
	if (this->_2DCamera) { EndMode2D(); } //? end 2Dmode
	///
	char s[50];
	sprintf(s, "totals hits = %u", hits);
	DrawText(s, 4,20, 30, BLUE);
	DrawFPS(0,0);
	char ss[50];
	// sprintf(ss, "pos x: %.0f, pos y: %.0f", Engine::getInstance().objectList[objectList.size()-1]->position.x, Engine::getInstance().objectList[objectList.size()-1]->position.y);
	DrawText(ss, 4, 60, 30, BLUE);
	for (size_t i = 0; i < uiRenderList.size(); i++) {
		if (uiRenderList[i] && uiRenderList[i]->texture) {
			const Object& tmp = *uiRenderList[i];
			DrawTextureEx(*tmp.texture, tmp.position, 0, 1, WHITE);
		}
	}
	//mouse test
	Mouse.setWindowSize({90,50});
}