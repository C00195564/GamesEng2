#pragma once
#include "stdafx.h"
#include "Commands.h"
#include "MacroCommand.h"

class Game
{
public:
	bool isRunning;
	Game();
	~Game();
	
	void initialise();
	void Update();
	void HandleEvents(SDL_Event action);
	void Render();
	void cleanup();
	Command* jump;
	Command* fire;
	Command* swap;
	Command* lurch;

	MacroCommand m_undoList;
	MacroCommand m_redoList;
	

};