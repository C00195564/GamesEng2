#pragma once
#include "State.h"
class Jumping : public State
{
public:
	Jumping() {};
	~Jumping() {};
	void idle(Animation* a)
	{
		std::cout << "Going from Jumping to Idling" << std::endl;
		a->setcurrent(new Idle());
		delete this;
	}
};