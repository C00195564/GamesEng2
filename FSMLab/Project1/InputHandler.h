#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include "Animation.h"
#include <SDL_events.h>
class InputHandler
{
public:
	InputHandler();
	~InputHandler();
	SDL_Event event;
	void HandleEvents(Animation* fsm, int &width, int &height, int &animation);
};

#endif // !INPUTHANDLER_H