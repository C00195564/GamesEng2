#include "Idle.h"

void Idle::jumping(Animation* a)
{
	std::cout << "jumping" << std::endl;
	a->setcurrent(new Idle());
	delete this;
}

void Idle::climbing(Animation* a)
{
	std::cout << "climbing" << std::endl;
	a->setcurrent(new Idle());
	delete this;
}