#include "Animation.h"
#include <thread>
#include <chrono>
#include "InputHandler.h"
#include <SDL_image.h>

int main(int argc, char* argv[]) {

	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	
	InputHandler iHandler;

	SDL_Window * window = SDL_CreateWindow("Finite State Machine",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

	//background image
	//SDL_Surface * image = IMG_Load("image.jpg");
	//SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);

	//SDL_RenderCopy(renderer, texture, NULL, NULL);
	//end of background

	//Beginning of character drawing/creation

	SDL_Surface * character = IMG_Load("crash.png");

	SDL_Texture * text = SDL_CreateTextureFromSurface(renderer, character);
	int spriteWidth = 23;
	int spriteHeight = 39;
	int animation = 97;
	//end of character drawing/creation

	//draw the screen
	SDL_RenderPresent(renderer);
	
	Animation* fsm = new Animation();


	
	bool running = true;
	while (running)
	{
		//Beginning of animation
		Uint32 ticks = SDL_GetTicks();
		Uint32 seconds = ticks / 100;
		Uint32 sprite = seconds % 10;
		//ending of animation

		int i = 0;
		iHandler.HandleEvents(fsm, spriteWidth, spriteHeight, animation);
		/*if (i == 0)
		{
			fsm->jumping();
			std::this_thread::sleep_for(std::chrono::milliseconds::duration(1000));
			i = 1;
		}
		else
		{
			fsm->climbing();
			std::this_thread::sleep_for(std::chrono::milliseconds::duration(1000));
			i = 0;
		}*/

		
		//Draw area
		SDL_Rect* srcrect = new SDL_Rect{ (int)sprite * spriteWidth, animation, spriteWidth, spriteHeight };
		SDL_Rect* dstrect = new SDL_Rect{ 10, 10, spriteWidth, spriteHeight };

		//SDL_RenderCopy(renderer, texture, srcrect, dstrect);
		
		SDL_RenderCopy(renderer, text, srcrect, dstrect);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
	}
	

	//SDL_DestroyTexture(texture);
	//SDL_FreeSurface(image);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();

	return 0;
}