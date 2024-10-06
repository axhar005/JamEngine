# include "../include/Trigger.h"

Trigger::Trigger(Vector2 _pos, Vector2 _size) :  Object(_pos, false), target(NULL) {
	hitList.reserve(10);
	this->hitbox.box.height = _size.y;
	this->hitbox.box.width = _size.x;
	this->drawTrigger = false;
}

Trigger::Trigger(Object* _target, Vector2 _size) : Object(_target->position, false), target(_target) {
	hitList.reserve(10);
	this->hitbox.box.height = _size.y;
	this->hitbox.box.width = _size.x;
	this->drawTrigger = false;
}

Trigger::~Trigger() {};

void  Trigger::step() {
	this->hitbox.box.x = this->position.x;
	this->hitbox.box.y = this->position.y;
}

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

void Trigger::draw(void) {
	if (drawTrigger)
		DrawRectangleRec(hitbox.box, {255,128,0,100});
}

// if you want to see that the zone were the box overlap
#define drawBox false

std::vector<int> Trigger::hit(void) {
	std::vector<int> result;
	result.reserve(hitList.size() / 2);
	for (size_t i = 0; i < hitList.size(); i++) {
		if (CheckCollisionRecs(this->hitbox.box, hitList[i]->hitbox.box)) {
			result.push_back(hitList[i]->id);
			#if (drawBox)
			{
				const Color box = {0, 255, 0, 100};
				const Rectangle rec = GetCollisionRec(this->hitbox.box, hitList[i]->hitbox.box);
				DrawRectangleRec(rec, box);
			}
			#endif
		}
	}
	return result;
}
