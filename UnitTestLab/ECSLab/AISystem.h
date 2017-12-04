#pragma once
#include "Entity.h"
#include "PositionComponent.h"
#include <vector>
#include <iostream>

class AISystem
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
		std::cout << "AI system updating" << std::endl;
		for (int i = 0; i < entities.size(); i++)
		{
			//Find position component and update position
		}
	}
};