#pragma once
#include "Component.h"
#include <vector>
class PositionComponent : public Component
{
public:
	PositionComponent() : position(50,50) {};
	struct Position
	{
	public:
		Position(float X, float Y)
		{
			m_x = X;
			m_y = Y;
		};
		float m_x = 0;
		float m_y = 0;
	};

	Position GetPosition() { return position; }

private:
	Position position;
};