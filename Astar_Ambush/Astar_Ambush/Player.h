#pragma once
#include "stdafx.h"
#include "InputHandler.h"

class Player
{
public:
	Player(CD_Vector position, float size, InputHandler *handler);
	~Player();
	void Update();
	void Draw(SDL_Renderer *rend);
	CD_Vector GetPos() { return m_position; };
	float getsize() { return m_size; };
	SDL_Rect* GetRect() { return &m_rect; };
	void movePlayer(float x, float y);

private:
	InputHandler *m_iHandler;
	const float m_moveSpeed = 2.0f;
	CD_Vector m_position;
	SDL_Rect m_rect;
	float m_size;

};

