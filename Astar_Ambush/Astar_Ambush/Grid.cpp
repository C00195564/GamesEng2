#include "Grid.h"


#define PIXELSIZE_SMALL 31
#define PIXELSIZE_MEDIUM 11
#define PIXELSIZE_LARGE 3

bool finished = false;;

Grid::Grid(Size size = Small)
{
	finished = false;
	if (size == Small)
	{
		height = 30;
		width = 30;
		for (int i = 0; i < height; i++)
		{
			std::vector<Cell> row;
			for (int j = 0; j < width; j++)
			{
				row.push_back(Cell(i, j, true, PIXELSIZE_SMALL));
			}
			m_grid.push_back(row);
		}

		//define the 3 inner walls
		//left wall
		for (int i = 1; i < 19; i++)
		{
			m_grid.at(7).at(i).m_active = false;
			m_walls.push_back(&m_grid.at(7).at(i));
		}

		//Center wall
		for (int i = 5; i < 27; i++)
		{
			m_grid.at(14).at(i).m_active = false;
			m_walls.push_back(&m_grid.at(14).at(i));
		}

		//right wall
		for (int i = 3; i < 25; i++)
		{
			m_grid.at(21).at(i).m_active = false;
			m_walls.push_back(&m_grid.at(21).at(i));
		}

	}
	else if (size == Medium)
	{
		height = 100;
		width = 100;

		for (int i = 0; i < height; i++)
		{
			std::vector<Cell> row;
			for (int j = 0; j < width; j++)
			{
				row.push_back(Cell(i, j, true, PIXELSIZE_MEDIUM));
			}
			m_grid.push_back(row);
		}
		//define the 3 inner walls
		//left wall
		for (int i = 1; i < 64; i++)
		{
			m_grid.at(24).at(i).m_active = false;
			m_walls.push_back(&m_grid.at(24).at(i));
		}

		//Center wall
		for (int i = 17; i < 90; i++)
		{
			m_grid.at(47).at(i).m_active = false;
			m_walls.push_back(&m_grid.at(47).at(i));
		}

		//right wall
		for (int i = 10; i < 84; i++)
		{
			m_grid.at(70).at(i).m_active = false;
			m_walls.push_back(&m_grid.at(70).at(i));
		}
	}
	else
	{
		height = 1000;
		width = 1000;

		for (int i = 0; i < height; i++)
		{
			std::vector<Cell> row;
			for (int j = 0; j < width; j++)
			{
				row.push_back(Cell(i, j, true, PIXELSIZE_LARGE));
			}
			m_grid.push_back(row);
		}
		//define the 3 inner walls
		//left wall
		for (int i = 1; i < 634; i++)
		{
			m_grid.at(234).at(i).m_active = false;
			m_walls.push_back(&m_grid.at(234).at(i));
		}

		//Center wall
		for (int i = 167; i < 900; i++)
		{
			m_grid.at(467).at(i).m_active = false;
			m_walls.push_back(&m_grid.at(467).at(i));
		}

		//right wall
		for (int i = 100; i < 834; i++)
		{
			m_grid.at(700).at(i).m_active = false;
			m_walls.push_back(&m_grid.at(700).at(i));
		}
	}


	//define walls for top and bottom sides of grid
	for (int i = 0; i < width; i++)
	{
		m_grid.at(0).at(i).m_active = false;
		m_grid.at(height - 1).at(i).m_active = false;
		m_walls.push_back(&m_grid.at(0).at(i));
		m_walls.push_back(&m_grid.at(height - 1).at(i));
	}

	//define walls for left and right sides of grid
	for (int i = 0; i < height; i++)
	{
		m_grid.at(i).at(0).m_active = false;
		m_grid.at(i).at(width - 1).m_active = false;
		m_walls.push_back(&m_grid.at(i).at(0));
		m_walls.push_back(&m_grid.at(i).at(width - 1));
	}

	Reset();
}

typedef struct
{
	Player* player;

	std::vector<Cell*> *walls;
}CollisionWrapper;



Grid::~Grid()
{
	finished = true;
	SDL_WaitThread(colThread, NULL);
}


void Grid::Draw(SDL_Renderer *renderer)
{
	for (int i = 0; i < m_grid.size(); i++)
	{
		for (int j = 0; j < m_grid.at(i).size(); j++)
		{
			m_grid.at(i).at(j).Draw(renderer);
		}
	}
}

void Grid::AddLinks()
{
	//i = x, j = y
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (m_grid[i][j].m_active)
			{
				//right
				if (m_grid[i][j].GetGridPosition().x < width - 1)
				{
					if (m_grid[i + 1][j].m_active)
					{
						m_grid[i][j].neighbours.emplace_back(new Link(&m_grid[i + 1][j]));
					}
				}
				//bottom
				if (m_grid[i][j].GetGridPosition().y < height - 1)
				{
					if (m_grid[i][j + 1].m_active)
					{
						m_grid[i][j].neighbours.emplace_back(new Link(&m_grid[i][j + 1]));
					}
				}
				//left
				if (m_grid[i][j].GetGridPosition().x > 0)
				{
					if (m_grid[i - 1][j].m_active)
					{
						m_grid[i][j].neighbours.emplace_back(new Link(&m_grid[i - 1][j]));
					}
				}
				//top
				if (m_grid[i][j].GetGridPosition().y > 0)
				{
					if (m_grid[i][j - 1].m_active)
					{
						m_grid[i][j].neighbours.emplace_back(new Link(&m_grid[i][j - 1]));
					}
				}
			}
			////top-left
			//if (grid[i][j]->GetGridPosition().x > 0 && grid[i][j]->GetGridPosition().x > 0)
			//{
			//	if (grid[i - 1][j - 1]->m_active)
			//	grid[i][j]->neighbours.emplace_back(grid[i - 1][j - 1]);
			//}
			////bottom-left
			//if (grid[i][j]->GetGridPosition().x < ROOM_HEIGHT - 1 && grid[i][j]->GetGridPosition().y < ROOM_WIDTH - 2)
			//{
			//	if (grid[i + 1][j + 1]->m_active)
			//	grid[i][j]->neighbours.emplace_back(grid[i + 1][j + 1]);
			//}
			////top-right
			//if (grid[i][j]->GetGridPosition().x < ROOM_HEIGHT - 1 && grid[i][j]->GetGridPosition().y > 0)
			//{
			//	if (grid[i + 1][j - 1]->m_active)
			//	grid[i][j]->neighbours.emplace_back(grid[i + 1][j - 1]);
			//}
			////bottom-right
			//if (grid[i][j]->GetGridPosition().x > 0 && grid[i][j]->GetGridPosition().y < ROOM_HEIGHT - 1)
			//{
			//	if (grid[i - 1][j + 1]->m_active)
			//	grid[i][j]->neighbours.emplace_back(grid[i - 1][j + 1]);
			//}
		}
	}
}



int Collisionfunc(void* data)
{
	CollisionWrapper *ptr = reinterpret_cast<CollisionWrapper*>(data);
	Player* player = ptr->player;
	std::vector<Cell*> *m_walls = ptr->walls;

	free(ptr);
	while (true)
	{
		if (finished == true)
		{
			std::cout << "exiting collision thread" << std::endl;
			break;
		}

		for (int i = 0; i < m_walls->size(); i++)
		{
			SDL_Rect *temp = new SDL_Rect();
			//check for collision.
			if (SDL_IntersectRect(player->GetRect(), m_walls->at(i)->GetRect(), temp));
			{

				//Collision response
				{

					//determine of it is a top/bottom or left/right collision

					if (temp->w < 0 || temp->h < 0)
					{

					}
					else
					{
						//if the width of intersection is less than the height of intersection
						if (temp->w < temp->h)
						{

							//left collision
							if (player->GetRect()->x > m_walls->at(i)->GetRect()->x)
							{
								player->movePlayer(temp->w, 0);
							}
							//right collision
							else /*if (temp->x + temp->w < m_walls.at(i)->GetRect()->x + m_walls.at(i)->GetRect()->w)*/
							{
								player->movePlayer(-temp->w, 0);
							}
						}
						else
						{
							//top collision
							if (player->GetRect()->x > m_walls->at(i)->GetRect()->y)
							{
								player->movePlayer(0, temp->h);
							}
							//bottom collision
							else /*if (temp->y + temp->h == m_walls.at(i)->GetRect()->y + m_walls.at(i)->GetRect()->h)*/
							{
								player->movePlayer(0, -temp->h);
							}
						}
					}
				}
			}
			free(temp);
		}
	}

	return 0;
}

void Grid::StartCollision(Player *player)
{
	CollisionWrapper *wrapper = new CollisionWrapper;
	wrapper->player = player;
	wrapper->walls = &m_walls;
	colThread = SDL_CreateThread(Collisionfunc, "collision thread", wrapper);
}

/// <summary>
/// Checks the collision between Cells marked inactive and the player
/// Should only check collision if the player is close to Cell
/// </summary>
/// <param name="player"></param>
void Grid::collision(Player *player)
{
	for (int i = 0; i < m_walls.size(); i++)
	{
		SDL_Rect *temp = new SDL_Rect();
		//check for collision.
		if (SDL_IntersectRect(player->GetRect(), m_walls.at(i)->GetRect(), temp));
		{
			
			//Collision response
			{

				//determine of it is a top/bottom or left/right collision

				if (temp->w < 0 || temp->h < 0)
				{

				}
				else
				{
					//if the width of intersection is less than the height of intersection
					if (temp->w < temp->h)
					{

						//left collision
						if (player->GetRect()->x > m_walls.at(i)->GetRect()->x)
						{
							player->movePlayer(temp->w, 0);
						}
						//right collision
						else /*if (temp->x + temp->w < m_walls.at(i)->GetRect()->x + m_walls.at(i)->GetRect()->w)*/
						{
							player->movePlayer(-temp->w, 0);
						}
					}
					else
					{
						//top collision
						if (player->GetRect()->x > m_walls.at(i)->GetRect()->y)
						{
							player->movePlayer(0, temp->h);
						}
						//bottom collision
						else /*if (temp->y + temp->h == m_walls.at(i)->GetRect()->y + m_walls.at(i)->GetRect()->h)*/
						{
							player->movePlayer(0, -temp->h);
						}
					}
				}
			}
		}
		
	}
}

Cell* Grid::GetNearestCell(CD_Vector pos)
{
	//map the position to the grid
	int tempi = (pos.x / width);
	int tempj = (pos.y / height);
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
	Cell* cell = &m_grid.at(tempi).at(tempj);
	return cell;
}


void Grid::Reset()
{
	for (auto i : m_grid)
	{
		for (auto j : i)
		{
			j.clear();
		}
	}
}