# include "../include/Trigger.h"



Trigger::Trigger(Vector2 pos) :  Object(pos), target(NULL) {
	hitList.reserve(10);
}

Trigger::~Trigger() {};


void  Trigger::add(Object* obj) {
	if (obj) { hitList.push_back(obj); }
}

void  Trigger::add(std::vector<Object*>& objs) {
	for (size_t i = 0; i < objs.size(); i++) {
		this->add(objs[i]);
	}
}

void Trigger::remove(int id) {
	for (size_t i = 0; hitList.size(); i++) {
		if (hitList[i]->id  == id) {
			hitList[i] = NULL;
			return ;
		}
	}
}

void Trigger::setTarget(Object* targetPtr) {
	if (targetPtr) { this->target = targetPtr; }
}

void Trigger::draw(){
	DrawRectangleRec(hitbox.box, {255,255,0,255});
}

#define drawBox 1

std::vector<int> Trigger::hit(void) {
	std::vector<int> result;
	result.reserve(hitList.size() / 2);
	for (size_t i = 0; i < hitList.size(); i++) {
		if (CheckCollisionRecs(this->hitbox.box, hitList[i]->hitbox.box)) {
			result.push_back(hitList[i]->id);
			#if (drawBox)
			{
				const Color box = {255, 255, 0, 255};
				const Rectangle rec = GetCollisionRec(this->hitbox.box, hitList[i]->hitbox.box);
				DrawRectangleRec(rec, box);
			}
			#endif
		}
	}
	return result;
}
