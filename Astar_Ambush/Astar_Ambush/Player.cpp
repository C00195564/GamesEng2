#include "Player.h"



Player::Player(CD_Vector position, float size, InputHandler *handler)
{
	m_iHandler = handler;
	m_position = position;
	m_rect.x = position.x;
	m_rect.y = position.y;
	m_rect.h = size;
	m_rect.w = size;
	m_size = size;
}


Player::~Player()
{

}

void Player::Update()
{
	if (m_iHandler->isPressed(SDLK_w))
	{
		m_position.y -= m_moveSpeed;
		m_rect.y -= m_moveSpeed;
	}
	if (m_iHandler->isPressed(SDLK_s))
	{
		m_position.y += m_moveSpeed;
		m_rect.y += m_moveSpeed;
	}
	if (m_iHandler->isPressed(SDLK_a))
	{
		m_position.x -= m_moveSpeed;
		m_rect.x -= m_moveSpeed;
	}
	if (m_iHandler->isPressed(SDLK_d))
	{
		m_position.x += m_moveSpeed;
		m_rect.x += m_moveSpeed;
	}
}

void Player::Draw(SDL_Renderer *rend)
{
	SDL_SetRenderDrawColor(rend, 0, 255, 0, 255);
	SDL_RenderFillRect(rend, &m_rect);
}

void Player::movePlayer(float x, float y)
{
	m_position.x += x;
	m_position.y += y;

	m_rect.x += x;
	m_rect.y += y;
}