#include "InputHandler.h"

InputHandler::InputHandler()
{
}

InputHandler::~InputHandler()
{
}

void InputHandler::HandleEvents(Animation* fsm, int &width, int &height, int &animation)
{
	while (SDL_PollEvent(&event))
	{
		switch (event.type) {
		case SDL_QUIT:
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				break;
			case SDLK_a:
				fsm->jumping();
				width = 25;
				height = 49;
				animation = 48;
				break;
			case SDLK_s:
				fsm->climbing();
				width = 23;
				height = 47;
				animation = 0;
				break;
			case SDLK_d:
				break;
			case SDLK_w:
				break;
			}
			break;

		case SDL_KEYUP:
			fsm->idle();
			width = 23;
			height = 39;
			animation = 97;
		}

	}
}
