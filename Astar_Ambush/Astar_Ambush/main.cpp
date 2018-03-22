#include <SDL.h>
#include <thread>
#include <iostream>
#include <vector>
#include "LTimer.h"
#include "Grid.h"


#define FRAMES_PER_SECOND 30
#define SCREEN_TICKS_PER_FRAME 1000 / FRAMES_PER_SECOND

#define THREAD_NUM std::thread::hardware_concurrency()


int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	std::cout << "threads available on this machine: " << THREAD_NUM << std::endl;
	std::vector<std::thread> threadPool;
	SDL_Window * window = SDL_CreateWindow("A*mbush",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	100, 100, 0);
	


	Grid *grid;
	bool init = false;
	while (init == false)
	{
		std::cout << "What size grid?" << std::endl;
		std::cout << "1 for 6 x 5 (30 cells, 5 enemies)" << std::endl;
		std::cout << "2 for 10 x 10 (100 cells, 50 enemies)" << std::endl;
		std::cout << "3 for 50 x 20 (1000 cells, 500 enemies)" << std::endl;
		int num = 0;
		std::cin >> num;
		if (num == 1)
		{
			grid = new Grid(Small);
			SDL_SetWindowSize(window, grid->width * 100, grid->height * 100);
			
			init = true;
		}
		else if (num == 2)
		{
			grid = new Grid(Medium);
			SDL_SetWindowSize(window, grid->width * 100, grid->height * 100);
			std::cout << (grid->width) << " " << (grid->height) << std::endl;
			init = true;
		}
		else if (num == 3)
		{
			grid = new Grid(Large);
			SDL_SetWindowSize(window, grid->width * 20, grid->height * 20);
			std::cout << (grid->width) << " " << (grid->height) << std::endl;
			init = true;
		}
		else
		{
			std::cout << "command not recognised" << std::endl;
		}
	}

	

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

		while (SDL_PollEvent(&evt))
		{
			if (evt.type == SDL_KEYDOWN)
			{

			}
			else if (evt.type == SDL_KEYUP)
			{
				 
			}
		}

		SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
		SDL_RenderClear(renderer);



		SDL_RenderPresent(renderer);

		int frameTicks = captimer.getTicks();
		if (frameTicks < SCREEN_TICKS_PER_FRAME)
		{
			//Wait remaining time
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
		}
		framecounter++;
	}


	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
