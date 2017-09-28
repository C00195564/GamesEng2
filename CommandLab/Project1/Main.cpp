#include "stdafx.h"
#include "Game.h"



int main(int argc, char* argv[]) {

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;

	window = SDL_CreateWindow("TUTORIAL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1080, 720, SDL_WINDOW_SHOWN);

	cout << "GameObject Created" << endl;
	Game* game = new Game();

	game->initialise();
	cout << "Initialising game object" << endl;
	cout << "Game Loop Starting.." << endl;



	SDL_Event event = SDL_Event();

	while (game->isRunning)
	{
		game->HandleEvents(event);
		game->Update();
		game->Render();
	}
	cout << "Calling cleanup" << endl;
	game->cleanup();
	return 0;
}

