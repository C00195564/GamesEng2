#pragma once
#include <iostream>
#include "Vehicle.h"

class Car : public Vehicle {
public:
	void draw() {
		std::cout << "Draw Car" << std::endl;
	}
};