#pragma once
#include "stdafx.h"

/// <summary>
/// NPC class
/// On its creation it's given a random number m_cellFollow between 1 & 5
/// if the npc has no path it requests the threadpool for one
/// NPC follows the path for m_cellFollow number of cells  before requesting a new path.
/// If the threadpool has yet to return a new path yet, keep following the old path.
/// </summary>
class NPC
{
public:
	NPC(CD_Vector position, float size, float acceleration);
	~NPC();
	void Update();
	void Draw(SDL_Renderer *rend);
	CD_Vector GetPos() { return m_position; };
	float getsize() { return m_size; };
	bool requestPath;

private:
	int m_TimeToRequest;
	int m_followCount;
	CD_Vector m_position;
	SDL_Rect m_rect;
	float m_size;
	std::vector<CD_Vector> m_path;
	CD_Vector m_currentTarget;

	float m_speed;
	CD_Vector m_velocity;
	CD_Vector m_nextpos;
	CD_Vector GetLinear(CD_Vector target);

};

