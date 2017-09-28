#include "Game.h"

Game::Game()
{
	isRunning = true;
}

Game::~Game()
{

}

void Game::initialise()
{
	jump = new JumpCommand();
	fire = new FireCommand();
	swap = new SwapCommand();
	lurch = new LurchCommand();
}

void Game::HandleEvents(SDL_Event event)
{
	while (SDL_PollEvent(&event))
	{
		switch (event.type) {
		case SDL_QUIT:
			this->isRunning = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				this->isRunning = false;
				break;
			case SDLK_a:
				fire->execute();
				m_undoList.Add(fire);
				m_redoList.Clear();
				break;
			case SDLK_s:
				swap->execute();
				m_undoList.Add(swap);
				m_redoList.Clear();
				break;
			case SDLK_d:
				lurch->execute();
				m_undoList.Add(lurch);
				m_redoList.Clear();
				break;
			case SDLK_w:
				jump->execute();
				m_undoList.Add(jump);
				m_redoList.Clear();
				break;
			case SDLK_r:
				cout << "redoing item" << endl;
				m_undoList.Add(m_redoList.undo());
				break;
			case SDLK_u:
				cout << "undoing item" << endl;
				m_redoList.Add(m_undoList.undo());
				break;
			}
			break;
		}

	}
}

void Game::Update()
{

}

void Game::Render()
{

}

void Game::cleanup()
{

}