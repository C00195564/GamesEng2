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
	JumpCommand* jump;
	FireCommand* fire;
	SwapCommand* swap;
	LurchCommand* lurch;

	MacroCommand m_undoList;
	MacroCommand m_redoList;
	

};