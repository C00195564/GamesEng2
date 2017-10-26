#pragma once
#include "Entity.h"
#include "ControlComponent.h"
#include <vector>
#include <iostream>

class ControlSystem
{
	std::vector<Entity> entities;

public:
	void addEntity(Entity e) { entities.push_back(e); };
	void removeEntity(Entity e)
	{
		for (int i = 0; i < entities.size(); i++)
		{
			//if (e == entities.at(i))
			//{
			//	//remove selected entity
			//}
		}
	}
	void update()
	{
		std::cout << "Control System updating" << std::endl;
	}

};