#pragma once
#include "stdafx.h"
#include<functional>
#include "NPC.h"
#include "Player.h"
#include "SDL_ThreadPool.h"

/// <summary>
/// Handles the creation, updating and drawing of NPC objects
/// checks when an NPC is requesting a path and enqueues a task with the threadpool
/// </summary>
class EnemyController
{
public:
	EnemyController() {};
	EnemyController(Size size,  Player *player, SDL_ThreadPool * pool, Grid * grid);
	~EnemyController();
	void update();
	void draw(SDL_Renderer *rend);

private:
	SDL_ThreadPool * m_tPool;
	Player *m_playerTarget;
	std::vector<NPC*> m_npcVec;
	Grid * m_grid;
};

