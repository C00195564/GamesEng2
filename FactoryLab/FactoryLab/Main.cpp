#include <vector>
#include "VehicleFactory.h"
using namespace std;

int main() {
	Factory* factory = new VehicleFactory();
	vector<Vehicle*> vehicles;
	vehicles.push_back(factory->CreateCar());
	vehicles.push_back(factory->CreateVan());

	for (int i = 0; i < vehicles.size(); i++)
	{
		vehicles[i]->draw();
	}
	system("PAUSE");
}