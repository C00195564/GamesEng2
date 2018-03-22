#pragma once
#include <cmath>
#include <vector>
#include <memory>
#include <iostream>
#include <array>
#include <limits>
#include "CD_Vector2f.h"

#define CELL_HEIGHT 64
#define CELL_WIDTH 64

/// <summary>
/// Class used to descibe part of the grid used for A* pathfinding
/// </summary>
class Cell
{
public:
	Cell(int i, int j, bool active, float cost = 1)
	{
		m_cost = cost;
		m_active = active;
		m_gridPosition.x = i;
		m_gridPosition.y = j;
		m_size.x = CELL_WIDTH;
		m_size.y = CELL_HEIGHT;
		m_position.x = m_gridPosition.x * m_size.x;
		m_position.y = m_gridPosition.y * m_size.y;
		m_origin.x = m_position.x + (CELL_WIDTH / 2);
		m_origin.y = m_position.y + (CELL_HEIGHT / 2);
		parent = nullptr;
		m_f = std::numeric_limits<int>::infinity();
		m_h = std::numeric_limits<int>::infinity();
		m_g = std::numeric_limits<int>::infinity();
	}

	Cell() {};
	~Cell() {};

	bool m_active;

	Cell *parent;
	std::vector<Cell*> neighbours;
	/// <summary>
	/// gets the straight line distance from one point to another
	/// </summary>
	/// <param name="goal">The poistion in the grid of the Target call</param>
	float CalculateH(CD_Vector target)
	{
		//manhatten distance heuristic
		return abs(m_gridPosition.x - target.x) + abs(m_gridPosition.y - target.y);
	}


	/// <summary>
	/// resets the node;
	/// </summary>
	void clear()
	{
		parent = nullptr;
		m_f = std::numeric_limits<int>::infinity();
		m_h = std::numeric_limits<int>::infinity();
		m_g = std::numeric_limits<int>::infinity();
	}

	float getF() { return m_f; };
	float getH() { return m_h; };
	float getG() { return m_g; };
	float getCost() { return m_cost; };
	CD_Vector GetGridPosition() { return m_gridPosition; };
	CD_Vector GetOrigin() { return m_origin; };
	void setCost(float cost) { m_cost = cost; };
	void setF(float f) { m_f = f; };
	void setH(float h) { m_h = h; };
	void setG(float g) { m_g = g; };

	bool operator==(const Cell other)
	{
		if (this->m_position == other.m_position)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

private:

	CD_Vector m_gridPosition;
	CD_Vector m_position;
	CD_Vector m_size;
	CD_Vector m_origin;
	float m_cost;
	float m_f; //g + h
	float m_g; //total cost from start
	float m_h; //heuristic value
};