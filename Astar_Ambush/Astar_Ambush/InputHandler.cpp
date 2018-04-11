#include "InputHandler.h"



InputHandler::InputHandler()
{
}


InputHandler::~InputHandler()
{
}

void InputHandler::handleKeyDownEvent(SDL_Event evt)
{
	m_keymap[evt.key.keysym.sym] = true;
}

void InputHandler::handleKeyUpEvent(SDL_Event evt)
{
	m_keymap[evt.key.keysym.sym] = false;
}

bool InputHandler::isPressed(SDL_Keycode key)
{
	return m_keymap[key];
}
