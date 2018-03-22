#include "Grid.h"



Grid::Grid(Size size = Small)
{
	if (size == Small)
	{
		height = 5;
		width = 6;
		for (int i = 0; i < height; i++)
		{
			std::vector<Cell> row;
			for (int j = 0; j < width; j++)
			{
				row.push_back(Cell(i, j, true));
			}
			m_grid.push_back(row);
		}

	}
	else if (size == Medium)
	{
		height = 10;
		width = 10;

		for (int i = 0; i < height; i++)
		{
			std::vector<Cell> row;
			for (int j = 0; width < 10; j++)
			{
				row.push_back(Cell(i, j, true));
			}
			m_grid.push_back(row);
		}
	}
	else
	{
		height = 20;
		width = 50;

		for (int i = 0; i < height; i++)
		{
			std::vector<Cell> row;
			for (int j = 0; j < width; j++)
			{
				row.push_back(Cell(i, j, true));
			}
			m_grid.push_back(row);
		}
	}


	//define walls for top and bottom sides of grid
	for (int i = 0; i < width; i++)
	{
		m_grid.at(0).at(i).m_active = false;
		m_grid.at(height - 1).at(i).m_active = false;
	}

	//define walls for laft and right sides of grid
	for (int i = 0; i < height; i++)
	{
		m_grid.at(i).at(0).m_active = false;
		m_grid.at(i).at(width - 1).m_active = false;
	}


}


Grid::~Grid()
{
}
