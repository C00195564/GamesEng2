#pragma once
#include "stdafx.h"
#include <memory>
#include <array>
#include <limits>
#include "Link.h"


/// <summary>
/// Class used to descibe part of the grid used for A* pathfinding
/// </summary>
class Cell
{
public:
	Cell(int i, int j, bool active, float size, float cost = 1);

	Cell() {};
	~Cell() {};

	void Draw(SDL_Renderer *renderer);
	bool m_active;

	Cell *parent;
	std::vector<Link*> neighbours;
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
	float getsize() { return m_rect.w; };
	SDL_Rect* GetRect() { return &m_rect; };
	CD_Vector GetGridPosition() { return m_gridPosition; };
	CD_Vector GetcenterPosition() { return m_origin; };
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
	float cellSize;
	CD_Vector m_gridPosition;
	CD_Vector m_position;
	SDL_Rect m_rect;
	CD_Vector m_size;
	CD_Vector m_origin;
	float m_cost;
	float m_f; //g + h
	float m_g; //total cost from start
	float m_h; //heuristic value
};