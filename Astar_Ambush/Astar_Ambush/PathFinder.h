#pragma once
#include "stdafx.h"
#include <memory>
#include <queue>
#include <iostream>
#include <array>
#include <limits>
#include "Grid.h"


#define CELL_HEIGHT 64
#define CELL_WIDTH 64

#define ROOM_WIDTH 12
#define ROOM_HEIGHT 12



class PathFinder
{
public:
	PathFinder();
	~PathFinder();

	/// <summary>
	/// Performs the A* search algorithm
	/// </summary>
	/// <param name="start">Cell the entity is currently in</param>
	/// <param name="target">Cell the target is in</param>
	/// <returns>vector of origins of cells on the path from start cell to target cell</returns>
	void AStar(Cell* start, Cell* target, std::vector<CD_Vector> *Path, bool* request);
};

