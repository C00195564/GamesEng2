#pragma once
#include <cmath>
#include <vector>
#include <memory>
#include <iostream>
#include <array>
#include <limits>
#include <SDL.h>
#include "CD_Vector2f.h"

#define CELL_HEIGHT 64
#define CELL_WIDTH 64

/// <summary>
/// Class used to descibe part of the grid used for A* pathfinding
/// </summary>
class Cell
{
public:
	Cell(int i, int j, bool active, float cost = 1);

	Cell() {};
	~Cell() {};

	void Draw(SDL_Renderer &renderer);
	bool m_active;

	Cell *parent;
	std::vector<Cell*> neighbours;
	/// <summary>
	/// gets the straight line distance from one point to another
	/// </summary>
	/// <param name="goal">The poistion in the grid of the Target call</param>
	float CalculateH(CD_Vector target);


	/// <summary>
	/// resets the node;
	/// </summary>
	void clear();

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