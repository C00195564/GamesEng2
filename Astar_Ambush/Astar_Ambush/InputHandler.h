#pragma once
#include "stdafx.h"
#include <map>
class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	void handleKeyDownEvent(SDL_Event evt);
	void handleKeyUpEvent(SDL_Event evt);
	bool isPressed(SDL_Keycode key);

private:
	std::map<SDL_Keycode, bool> m_keymap;
};

