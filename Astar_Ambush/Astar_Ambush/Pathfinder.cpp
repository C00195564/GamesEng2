#include "Pathfinder.h"

PathFinder::PathFinder(std::vector<std::vector<int>> layout)
{
	//for every row of the level Y
	for (int i = 0; i < layout.size(); i++)
	{
		//for every position in row X
		for (int j = 0; j < layout.at(i).size(); j++)
		{
			int num = layout.at(i).at(j);

			if (num == 7) //if the cell is empty activate the cell
			{
				grid[j][i] = new Cell(j, i, true);
			}
			else //wrong number given so just turn off the cell
			{
				grid[j][i] = new Cell(j, i, false);
			}
		}
	}
}

PathFinder::~PathFinder()
{

}

void PathFinder::Reset()
{
	ClearAll();
	for (int i = 0; i < ROOM_WIDTH; i++)
	{
		for (int j = 0; j < ROOM_HEIGHT; j++)
		{
			grid[i][j]->clear();
		}
	}
}

Cell* PathFinder::GetNearestCell(CD_Vector pos)
{
	//map the position to the grid
	int tempi = (pos.x / CELL_WIDTH);
	int tempj = (pos.y / CELL_HEIGHT);
	//if there is a remainder
	//if (((int)pos.x % CELL_WIDTH) > 0)
	//{
	//	tempi++;
	//}
	//if (((int)pos.y % CELL_HEIGHT) > 0)
	//{
	//	tempj++;
	//}
	//return the cell at that position
	Cell* cell = grid[tempi][tempj];
	return cell;
}

std::vector<CD_Vector> PathFinder::AStar(Cell* start, Cell* target)
{
	Reset();

	openSet.push_back(start);
	//while the openset is not empty
	while (openSet.size() > 0)
	{
		int smallest = 0;
		for (int i = 0; i < openSet.size(); i++)
		{
			if (openSet.at(i)->getF() < openSet.at(smallest)->getF())
			{
				smallest = i;
			}
		}

		Cell* current = openSet.at(smallest);

		//std::cout << current->GetGridPosition().x << " " << current->GetGridPosition().y << std::endl;

		//if the search has reached the target
		if (*current == *target)
		{
			std::vector<CD_Vector> path;
			path.push_back(current->GetOrigin());
			//std::cout << "Found target" << std::endl;
			//std::cout << "Path: " << current->GetGridPosition().x << " " << current->GetGridPosition().y << std::endl;
			//follow back through all the parent pointers to the first cell
			//First cell should be the only cell in the 
			while (current->parent != nullptr)
			{
				current = current->parent;
				//std::cout << "Path: " << current->GetGridPosition().x << " " << current->GetGridPosition().y << std::endl;
				path.push_back(current->GetOrigin());
			}

			return path;
		}

		openSet.erase(openSet.begin() + smallest);
		closedSet.push_back(current);

		//for every neighbour of the current node
		
		for(auto link : current->neighbours)
		{
			//if neighbour cell is not in closedset and the cell is active
			if (std::find(closedSet.begin(), closedSet.end(), link) == closedSet.end() && link->m_active == true)
			{
				int tempg = current->getG() + link->getCost();
				//if neighbour is not in the openset(not evaluated yet)
				if (std::find(openSet.begin(), openSet.end(), link) == openSet.end())
				{
					link->parent = current; //may break here
					link->setG(tempg);
					openSet.push_back(link);
				}
				else
				{
					if (link->getG() > tempg)
					{
						link->parent = current;
						link->setG(tempg);
					}
				}

				link->setH(link->CalculateH(target->GetGridPosition()));
				link->setF(link->getG() + link->getH());
			}
		}
	}

	std::cout << "Unable to find path" << std::endl;
	std::vector<CD_Vector> err;
	return err;
}

void PathFinder::AddLinks()
{
	for (int i = 0; i < ROOM_WIDTH; i++)
	{
		for (int j = 0; j < ROOM_HEIGHT; j++)
		{
			//right
			if (grid[i][j]->GetGridPosition().x < ROOM_WIDTH - 1)
			{
				if (grid[i + 1][j]->m_active)
				{
					grid[i][j]->neighbours.emplace_back(grid[i + 1][j]);
				}
			}
			//bottom
			if (grid[i][j]->GetGridPosition().x < ROOM_HEIGHT - 1)
			{
				if (grid[i][j + 1]->m_active)
					grid[i][j]->neighbours.emplace_back(grid[i][j + 1]);
			}
			//left
			if (grid[i][j]->GetGridPosition().x > 0)
			{
				if (grid[i - 1][j]->m_active)
					grid[i][j]->neighbours.emplace_back(grid[i - 1][j]);
			}
			//top
			if (grid[i][j]->GetGridPosition().y > 0)
			{
				if (grid[i][j - 1]->m_active)
					grid[i][j]->neighbours.emplace_back(grid[i][j - 1]);
			}
			//top-left
			if (grid[i][j]->GetGridPosition().x > 0 && grid[i][j]->GetGridPosition().x > 0)
			{
				if (grid[i - 1][j - 1]->m_active)
				grid[i][j]->neighbours.emplace_back(grid[i - 1][j - 1]);
			}
			//bottom-left
			if (grid[i][j]->GetGridPosition().x < ROOM_HEIGHT - 1 && grid[i][j]->GetGridPosition().y < ROOM_WIDTH - 2)
			{
				if (grid[i + 1][j + 1]->m_active)
				grid[i][j]->neighbours.emplace_back(grid[i + 1][j + 1]);
			}
			//top-right
			if (grid[i][j]->GetGridPosition().x < ROOM_HEIGHT - 1 && grid[i][j]->GetGridPosition().y > 0)
			{
				if (grid[i + 1][j - 1]->m_active)
				grid[i][j]->neighbours.emplace_back(grid[i + 1][j - 1]);
			}
			//bottom-right
			if (grid[i][j]->GetGridPosition().x > 0 && grid[i][j]->GetGridPosition().y < ROOM_HEIGHT - 1)
			{
				if (grid[i - 1][j + 1]->m_active)
				grid[i][j]->neighbours.emplace_back(grid[i - 1][j + 1]);
			}
		}
	}
}