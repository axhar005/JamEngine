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


#define drawBox 1

std::vector<int> Trigger::hit(void) {
	std::vector<int> result;
	result.reserve(hitList.size() / 2);
	for (size_t i = 0; i < hitList.size(); i++) {
		if (CheckCollisionRecs(this->hitbox, hitList[i]->hitbox)) {
			result.push_back(hitList[i]->id);
			#if (drawBox)
			{
				const Color box = {0, 0, 255, 70};
				const Rectangle rec = GetCollisionRec(this->hitbox, hitList[i]->hitbox);
				DrawRectangleRec(rec, box);
			}
			#endif
		}
	}
	return result;
	}
