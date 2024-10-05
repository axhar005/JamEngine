#ifndef TRIGER_H
# define TRIGER_H

# include "Object.h"
# include "engineSetup.h"


class Trigger : public Object {
	private:
		std::vector<Object*>	hitList;
		Object*					target;
	public:
		Trigger(Vector2 pos);
		~Trigger();
		void setTarget(Object* targetPtr);
	//
		void add(Object* obj);
		void add(std::vector<Object*>& objs);
		void remove(int id);
		std::vector<int> hit(void);
};


#endif