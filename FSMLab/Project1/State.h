#ifndef STATE_H
#define STATE_H

#include <iostream>
#include "Animation.h"
class State
{
public:
	virtual void idle(Animation* a)
	{
		std::cout << "State::Idling" << std::endl;
	}

	virtual void jumping(Animation* a)
	{
		std::cout << "State::Jumping" << std::endl;
	}

	virtual void climbing(Animation* a)
	{
		std::cout << "State::climbing" << std::endl;
	}

};

#endif // !STATE_H
