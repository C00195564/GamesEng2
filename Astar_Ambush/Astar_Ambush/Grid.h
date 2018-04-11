#pragma once
#include "stdafx.h"
#include "Cell.h"
#include "Player.h"
#include <SDL_thread.h>



class Grid
{
public:
	Grid() {};
	Grid(Size size);
	~Grid();
	void Draw(SDL_Renderer *Renderer);
	void AddLinks();
	int width;
	int height;
	Cell* GetNearestCell(CD_Vector pos);
	void StartCollision(Player *player);
	void collision(Player *player);
	bool finished;
private:
	SDL_Thread *colThread;
	std::vector<std::vector<Cell>> m_grid;
	std::vector<Cell*> m_walls;
	SDL_Texture * texture;
	SDL_Rect rect;
};

