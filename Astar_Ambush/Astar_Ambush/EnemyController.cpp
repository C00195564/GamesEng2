#include "EnemyController.h"

SDL_mutex *aStarMutex;

typedef struct {
	Cell * NPC;
	Cell * Player;
	std::vector<CD_Vector> *path;
	bool *request;
	Grid* grid;
}AstarHolder;

void AStar(void *args)
{
	SDL_LockMutex(aStarMutex);
	std::cout << "starting task" << std::endl;
	AstarHolder* holder = reinterpret_cast<AstarHolder*>(args);
	std::vector<Cell*> openSet;
	std::vector<Cell*> closedSet;
	Cell* m_start = holder->NPC;
	Cell* m_target = holder->Player;
	
	openSet.push_back(m_start);
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
		if (*current == *m_target)
		{
			std::vector<CD_Vector> newpath;
			newpath.push_back(current->GetOrigin());
			//std::cout << "Found target" << std::endl;
			//std::cout << "Path: " << current->GetGridPosition().x << " " << current->GetGridPosition().y << std::endl;
			//follow back through all the parent pointers to the first cell
			//First cell should be the only cell in the 
			while (current->parent != nullptr)
			{
				current = current->parent;
				//std::cout << "Path: " << current->GetGridPosition().x << " " << current->GetGridPosition().y << std::endl;
				newpath.push_back(current->GetOrigin());
			}
			//elements have been pushed to vector from target to beginning.
			//reverse the elements so beginning of the path is at the from of the vector
			std::reverse(newpath.begin(), newpath.end());
			//send the path back to the NPC who requested it
			
			*holder->path = newpath;
			
			//Let the NPC know it has a new path to follow
			*holder->request = false;

			holder->grid->Reset();
			free(holder);
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

				link->getCell()->setH(link->getCell()->CalculateH(m_target->GetGridPosition()));
				link->getCell()->setF(link->getCell()->getG() + link->getCell()->getH());
			}
		}
	}
	std::cout << "done" << std::endl;
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
			m_npcVec.push_back(new NPC(CD_Vector(PIXELSIZE_SMALL * (int)(Small * 0.9),
				PIXELSIZE_SMALL * (int)(Small * 0.5)), PIXELSIZE_SMALL, 2.0f));
		}
		break;
	case Size::Medium:
		for (int i = 0; i < 50; i++)
		{
			m_npcVec.push_back(new NPC(CD_Vector(PIXELSIZE_MEDIUM * (int)(Medium * 0.9),
				PIXELSIZE_MEDIUM * (int)(Medium * 0.5)), PIXELSIZE_MEDIUM, 1.0f));
		}
		break;
	case Size::Large:
		for (int i = 0; i < 500; i++)
		{
			m_npcVec.push_back(new NPC(CD_Vector(PIXELSIZE_LARGE* (int)(Large * 0.9), 
				PIXELSIZE_LARGE* (int)(Large * 0.5)), PIXELSIZE_LARGE, 0.5f));
		}
		break;
	default:
		break;
	}

}


EnemyController::~EnemyController()
{
}


/// <summary>
/// Updates the NPC's 
/// checks if an npc is requesting a path and queues a task with the threadpool
/// </summary>
void EnemyController::update()
{
	for (auto i : m_npcVec)
	{
		i->Update();
		if (i->requestPath)
		{
			AstarHolder *holder = new AstarHolder();
			holder->NPC = m_grid->GetNearestCell(i->GetPos());
			holder->Player = m_grid->GetNearestCell(m_playerTarget->GetPos());
			holder->path = i->GetPath();
			holder->request = &i->requestPath;
			holder->grid = m_grid;
			//m_tPool->enqueue(AStar, &holder);

			std::function<void()> e = std::bind(&AStar, holder);
			m_tPool->enqueue(e);
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


