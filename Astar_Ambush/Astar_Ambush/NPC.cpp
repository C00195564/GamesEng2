#include "NPC.h"



NPC::NPC(CD_Vector position, float size, float speed)
{
	m_speed = speed;
	m_position = position;
	m_rect.x = position.x;
	m_rect.y = position.y;
	m_rect.h = size;
	m_rect.w = size;
	m_size = size;
	m_TimeToRequest = rand() % 6 + 1;
	requestPath = true;
	m_currentTarget = m_position;
	int i;
}


NPC::~NPC()
{
}

void NPC::Update()
{
	//if we haven't requested a new path follow path as normal
	if (!requestPath)
	{
		m_currentTarget = m_path[m_followCount];
		
		//movement
		m_velocity = m_velocity + GetLinear(m_currentTarget) * m_speed;
		if (m_velocity.x > m_speed)
		{
			m_velocity.x = m_speed;
		}
		else if (m_velocity.x < -m_speed)
		{
			m_velocity.x = -m_speed;
		}
		if (m_velocity.y > m_speed)
		{
			m_velocity.y = m_speed;
		}
		else if (m_velocity.y < -m_speed)
		{
			m_velocity.y = -m_speed;
		}
		m_position += m_velocity;
		m_rect.x = m_position.x - m_rect.w;
		m_rect.y = m_position.y - m_rect.h;

		
		//if we reached our target
		if (m_position.Distance(m_currentTarget) < 2)
		{
			//increment our counter
			m_followCount++;
			//if we have reached our time to ceck
			if (m_followCount > m_TimeToRequest)
			{
				requestPath = true;
				m_followCount = 0;
			}
			else
			{
				//if we have reached the player
				if (m_followCount > m_path.size())
				{
					requestPath = true;
					m_followCount = 0;
				}
				else
				{
					//fetch the next target
					if (!m_path.empty())
					{
						m_currentTarget = m_path[m_followCount];
					}
				}
			}
		}
	}
}

void NPC::Draw(SDL_Renderer *rend)
{
	SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
	SDL_RenderFillRect(rend, &m_rect);
}

CD_Vector NPC::GetLinear(CD_Vector target)
{
	CD_Vector linear;
	linear = target - m_position;
	linear.Normalise();
	linear = linear * m_speed;

	return linear;
}