#pragma once
#include "Factory.h"

class VehicleFactory : public Factory {
public:
	Vehicle* CreateCar() {
		return new Car;
	}
	Vehicle* CreateVan() {
		return new Van;
	}
};