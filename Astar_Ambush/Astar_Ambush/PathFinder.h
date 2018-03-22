#pragma once
#include <cmath>
#include <vector>
#include <memory>
#include <iostream>
#include <array>
#include <limits>
#include "Cell.h"
#include "CD_Vector2f.h"


#define CELL_HEIGHT 64
#define CELL_WIDTH 64

#define ROOM_WIDTH 12
#define ROOM_HEIGHT 12



class PathFinder
{
public:
	PathFinder(std::vector<std::vector<int>> layout);
	PathFinder() {};
	~PathFinder();

	/// <summary>
	/// goes through the grid and resets all nodes and
	/// the open and closed sets
	/// </summary>
	void Reset();

	/// <summary>
	/// Finds the cell the position is in.
	/// ***Recommended to use the center origin of the entity***
	/// </summary>
	/// <param name="Pos">Position to check against</param>
	/// <returns>Pointer to the Cell the position is in </returns>
	Cell* GetNearestCell(CD_Vector Pos);

	void AddLinks();

	/// <summary>
	/// Performs the A* search algorithm
	/// </summary>
	/// <param name="start">Cell the entity is currently in</param>
	/// <param name="target">Cell the target is in</param>
	/// <returns>vector of origins of cells on the path from start cell to target cell</returns>
	std::vector<CD_Vector> AStar(Cell* start, Cell* target);
private:
	Cell * grid[ROOM_WIDTH][ROOM_HEIGHT];
	std::vector<Cell*> openSet;
	std::vector<Cell*> closedSet;
	Cell start;
	Cell target;


	void ClearAll()
	{
		start.clear();
		target.clear();
		openSet.clear();
		closedSet.clear();
	}
};

