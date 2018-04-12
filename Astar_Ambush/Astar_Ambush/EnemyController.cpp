#include "EnemyController.h"

SDL_mutex *aStarMutex;

void AStar(Cell* start, Cell* target, std::vector<CD_Vector> *Path, bool* request, Grid *grid)
{
	SDL_LockMutex(aStarMutex);
	std::vector<Cell*> openSet;
	std::vector<Cell*> closedSet;
	Cell* m_start = start;
	Cell* m_target = target;

	free(start);

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
			//elements have been pushed to vector from target to beginning.
			//reverse the elements so beginning of the path is at the from of the vector
			std::reverse(path.begin(), path.end());
			//send the path back to the NPC who requested it
			*Path = path;
			
			//Let the NPC know it has a new path to follow
			*request = false;
			grid->Reset();
			SDL_UnlockMutex(aStarMutex);
			break;
		}

		openSet.erase(openSet.begin() + smallest);

		closedSet.push_back(current);

		//for every neighbour of the current node

		for (Link* link : current->neighbours)
		{
			//if neighbour cell is not in closedset and the cell is active
			if (std::find(closedSet.begin(), closedSet.end(), link->getCell()) == closedSet.end() && link->getCell()->m_active == true)
			{
				int tempg = current->getG() + link->getCell()->getCost();
				//if neighbour is not in the openset(not evaluated yet)
				if (std::find(openSet.begin(), openSet.end(), link->getCell()) == openSet.end())
				{
					link->getCell()->parent = current;
					link->getCell()->setG(tempg);
					openSet.push_back(link->getCell());
				}
				else
				{
					if (link->getCell()->getG() > tempg)
					{
						link->getCell()->parent = current;
						link->getCell()->setG(tempg);
					}
				}

				link->getCell()->setH(link->getCell()->CalculateH(target->GetGridPosition()));
				link->getCell()->setF(link->getCell()->getG() + link->getCell()->getH());
			}
		}
	}
}

EnemyController::EnemyController(Size size, Player *player, SDL_ThreadPool* pool, Grid * grid)
{
	m_playerTarget = player;
	m_tPool = pool;
	m_grid = grid;
	aStarMutex = SDL_CreateMutex();
	switch (size)
	{
	case Size::Small:
		for (int i = 0; i < 5; i++)
		{
			float u = (rand() % 100 + 90) / 100;
			float v = (rand() % 100 + 90) / 100;
			m_npcVec.push_back(new NPC(CD_Vector(PIXELSIZE_SMALL * (int)(Small * u),
				PIXELSIZE_SMALL * (int)(Small * v)), PIXELSIZE_SMALL, 2.0f));
		}
		break;
	case Size::Medium:
		for (int i = 0; i < 50; i++)
		{
			float u = (rand() % 100 + 90) / 100;
			float v = (rand() % 100 + 90) / 100;
			m_npcVec.push_back(new NPC(CD_Vector(PIXELSIZE_MEDIUM * (int)(Medium * u),
				PIXELSIZE_MEDIUM * (int)(Medium * v)), PIXELSIZE_MEDIUM, 1.0f));
		}
		break;
	case Size::Large:
		for (int i = 0; i < 500; i++)
		{
			float u = (rand() % 100 + 90) / 100;
			float v = (rand() % 100 + 90) / 100;
			m_npcVec.push_back(new NPC(CD_Vector(PIXELSIZE_LARGE* (int)(Large * u), 
				PIXELSIZE_LARGE* (int)(Large * v)), PIXELSIZE_LARGE, 0.5f));
		}
		break;
	default:
		break;
	}

}


EnemyController::~EnemyController()
{
}

void EnemyController::update()
{
	for (auto i : m_npcVec)
	{
		i->Update();
		if (i->requestPath)
		{
			m_tPool->enqueue(AStar, m_grid->GetNearestCell(i->GetPos()),
				m_grid->GetNearestCell(m_playerTarget->GetPos()), i->GetPath(), &i->requestPath, m_grid);
		}
	}
	
}

void EnemyController::draw(SDL_Renderer *rend)
{
	for (auto i : m_npcVec)
	{
		i->Draw(rend);
	}
}

void EnemyController::Requestpath()
{
	//m_tPool->enqueue(m_pathFinder.AStar, )
}

