#pragma once
#include "stdafx.h"
#include "NPC.h"
#include "PathFinder.h"
#include "Player.h"
#include "SDL_ThreadPool.h"

/// <summary>
/// Handles the creation, updating and drawing of NPC objects
/// checks when an NPC is requesting a path and enqueues a task with the threadpool
/// </summary>
class EnemyController
{
public:

	EnemyController(Size size,  Player *player, SDL_ThreadPool * pool);
	~EnemyController();
	void update();
	void draw(SDL_Renderer *rend);
	void Requestpath();
private:
	SDL_ThreadPool * m_tPool;
	PathFinder m_pathFinder;
	Player *m_playerTarget;
	std::vector<NPC*> m_npcVec;
	
};

