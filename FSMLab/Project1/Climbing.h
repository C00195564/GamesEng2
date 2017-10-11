#pragma once
#include "State.h"

class Climbing : public State
{
public:
	Climbing() {};
	~Climbing() {};

	void idle(Animation* a)
	{
		std::cout << "Going from Climbing to Idling" << std::endl;
		a->setcurrent(new Idle());
		delete this;
	}
};