#pragma once
#include "Vehicle.h"
#include <iostream>

class Van : public Vehicle {
public:
	void draw()
	{
		std::cout << "Draw Player" << std::endl;
	}
};