#include <iostream>
#include <ctime>
#include "LTimer.h"
#include "Grid.h"
#include "Player.h"
#include "EnemyController.h"
#include "InputHandler.h"
#include "SDL_ThreadPool.h"
#include "stdafx.h"

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	srand(std::time(NULL));
	std::cout << "threads available on this machine: " << THREAD_NUM << std::endl;
	
	
	SDL_Window * window = SDL_CreateWindow("A*mbush",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	100, 100, 0);
	int frames = 0;

	InputHandler handler;
	Player * player = new Player(CD_Vector(62,62), 4, &handler);
	std::vector<NPC*> npcVec;
	EnemyController *eController = new EnemyController();
	Grid *grid = new Grid();
	bool init = false;
	
	std::cout << "What size grid?" << std::endl;
	std::cout << "1 for 30 x 30 (900 cells, 5 enemies)" << std::endl;
	std::cout << "2 for 100 x 100 (10,000 cells, 50 enemies)" << std::endl;
	std::cout << "3 for 1000 x 1000 (1,000,000 cells, 500 enemies)" << std::endl;
	int num = 0;
	std::cin >> num;
	SDL_ThreadPool *pool = new SDL_ThreadPool(5);
	if (num == 1)
	{
		grid = new Grid(Small);
		SDL_SetWindowSize(window, grid->width * PIXELSIZE_SMALL, grid->height * PIXELSIZE_SMALL);
		grid->AddLinks();
		player = new Player(CD_Vector(PIXELSIZE_SMALL, PIXELSIZE_SMALL), PIXELSIZE_SMALL, &handler);
		eController = new EnemyController(Small, player, pool, grid);
		init = true;
	}
	else if (num == 2)
	{
		grid = new Grid(Medium);
		SDL_SetWindowSize(window, grid->width * PIXELSIZE_MEDIUM, grid->height * PIXELSIZE_MEDIUM);
		std::cout << (grid->width) << " " << (grid->height) << std::endl;
		grid->AddLinks();
		player = new Player(CD_Vector(PIXELSIZE_MEDIUM, PIXELSIZE_MEDIUM), PIXELSIZE_MEDIUM, &handler);
		eController = new EnemyController(Medium, player, pool, grid);
		init = true;
	}
	else if (num == 3)
	{
		grid = new Grid(Large);
		SDL_SetWindowSize(window, grid->width * PIXELSIZE_LARGE, grid->height * PIXELSIZE_LARGE);
		std::cout << (grid->width) << " " << (grid->height) << std::endl;
		grid->AddLinks();
		player = new Player(CD_Vector(PIXELSIZE_LARGE, PIXELSIZE_LARGE), PIXELSIZE_LARGE, &handler);
		eController = new EnemyController(Large, player, pool, grid);
		init = true;
	}
	else
	{
		std::cout << num + " command not recognised" << std::endl;
	}
		
	
	
	grid->StartCollision(player);

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
	bool running = true;
	SDL_Event evt;

	int framecounter = 0;
	LTimer fpstimer;
	LTimer captimer;

	fpstimer.start();
	while (running)
	{
		captimer.start();
		float avgfps = framecounter / (fpstimer.getTicks() / 1000.0f);
		if (avgfps > 200000)
		{
			avgfps = 0;
		}

		//update player
		while (SDL_PollEvent(&evt))
		{
			switch (evt.type)
			{
			case SDL_KEYDOWN:
				handler.handleKeyDownEvent(evt);
				break;
			case SDL_KEYUP:
				handler.handleKeyUpEvent(evt);
			}
		}

		player->Update();

		eController->update();
		//grid->collision(player);

		SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
		SDL_RenderClear(renderer);

		//draw everything
		for (int i = 0; i < npcVec.size(); i++)
		{
			npcVec.at(i)->Draw(renderer);
		}
		
		grid->Draw(renderer);
		eController->draw(renderer);
		player->Draw(renderer);

		SDL_RenderPresent(renderer);
		
		
		if (frames < FRAMES_PER_SECOND)
		{
			frames = 0;
			//std::cout << "Frames per second: " << avgfps << std::endl;
		}

		//check if we finished too fast
		int frameTicks = captimer.getTicks();
		if (frameTicks < SCREEN_TICKS_PER_FRAME)
		{
			//Wait remaining time
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
			
		}
		frames++;
		framecounter++;
		
	}


	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}


