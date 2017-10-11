#ifndef ANIMATION_H
#define ANIMATION_H
#include <SDL.h>

class Animation {
	class State* current;
public:
	Animation();
	void setcurrent(State* s)
	{
		current = s;
	}
	void idle();
	void jumping();
	void climbing();
};

#endif // !ANIMATION_H