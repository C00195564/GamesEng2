#include "Cell.h"

Cell::Cell(int i, int j, bool active, float size, float cost)
{
	cellSize = size;
	m_cost = cost;
	m_active = active;
	m_gridPosition.x = i;
	m_gridPosition.y = j;
	m_size.x = cellSize;
	m_size.y = cellSize;
	
	m_position.x = m_gridPosition.x * m_size.x;
	m_position.y = m_gridPosition.y * m_size.y;
	m_rect = SDL_Rect();
	m_rect.x = m_position.x;
	m_rect.y = m_position.y;
	m_rect.h = cellSize;
	m_rect.w = cellSize;
	m_origin.x = m_position.x + (cellSize / 2);
	m_origin.y = m_position.y + (cellSize / 2);
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

void Cell::Draw(SDL_Renderer *renderer)
{
	//draw box aoround every cell, colour blue if inactive
	if (!m_active)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderFillRect(renderer, &m_rect);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderDrawRect(renderer, &m_rect);
	}
	else
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderDrawRect(renderer, &m_rect);
	}

	//draw links of cell
	//if even check
	if (m_rect.w > 5)
	{
		if ((int)m_gridPosition.y % 2 == 0)
		{
			if ((int)m_gridPosition.x % 2 == 0)
			{
				SDL_SetRenderDrawColor(renderer, 48, 299, 217, 122);
				for (auto i : neighbours)
				{
					SDL_RenderDrawLine(renderer, m_origin.x, m_origin.y, i->getCell()->GetcenterPosition().x, i->getCell()->GetcenterPosition().y);
				}
			}
		}
		else
		{
			if ((int)m_gridPosition.x % 2 != 0)
			{
				SDL_SetRenderDrawColor(renderer, 48, 299, 217, 122);
				for (auto i : neighbours)
				{
					SDL_RenderDrawLine(renderer, m_origin.x, m_origin.y, i->getCell()->GetcenterPosition().x, i->getCell()->GetcenterPosition().y);
				}
			}
		}
	}
}

