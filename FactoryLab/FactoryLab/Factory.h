#pragma once
#include "Car.h"
#include "Van.h"

class Factory {
public:
	virtual Vehicle* CreateCar() = 0;
	virtual Vehicle* CreateVan() = 0;
};