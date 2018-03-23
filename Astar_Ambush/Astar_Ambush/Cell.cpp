#include "Cell.h"

Cell::Cell(int i, int j, bool active, float cost = 1)
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

float Cell::CalculateH(CD_Vector target)
{
	//manhatten distance heuristic
	return abs(m_gridPosition.x - target.x) + abs(m_gridPosition.y - target.y);
}

void Cell::clear()
{
	parent = nullptr;
	m_f = std::numeric_limits<int>::infinity();
	m_h = std::numeric_limits<int>::infinity();
	m_g = std::numeric_limits<int>::infinity();
}

void Cell::Draw(SDL_Renderer &renderer)
{
	
}