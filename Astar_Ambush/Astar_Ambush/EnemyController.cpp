#include "EnemyController.h"



EnemyController::EnemyController(Size size, Player *player, SDL_ThreadPool* pool)
{
	m_playerTarget = player;
	m_tPool = pool;

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