#include "Idle.h"
#include "Jumping.h"
#include "Climbing.h"
void Idle::jumping(Animation* a)
{
	std::cout << "jumping" << std::endl;
	a->setcurrent(new Jumping());
	delete this;
}

void Idle::climbing(Animation* a)
{
	std::cout << "climbing" << std::endl;
	a->setcurrent(new Climbing());
	delete this;
}