#ifndef TRIGER_H
# define TRIGER_H

# include "Object.h"
# include "engineSetup.h"


class Trigger : public Object {
	private:
		std::vector<Object*>	hitList;
		Object*					target;
	public:
		bool drawTrigger;
		Trigger(Vector2 _pos, Vector2 _size);
		Trigger(Object* _target, Vector2 _size);
		~Trigger();
		void setTarget(Object* targetPtr);
		void step();
	//
		void add(Object* obj);
		void add(std::vector<Object*>& objs);
		void remove(int id);
		void draw(void);
		std::vector<int> hit(void);
};


#endif