#pragma once
#include <cmath>

struct CD_Vector
{
	CD_Vector();
	CD_Vector(float xPos, float yPos);
	void operator=(CD_Vector right);
	void operator*=(float value);
	void operator+=(CD_Vector right);
	CD_Vector operator+(CD_Vector right);
	CD_Vector operator-(CD_Vector right);
	float operator*(CD_Vector right);
	CD_Vector operator*(float right);
	bool operator==(const CD_Vector other);
	void Normalise();
	float Length();
	float x;
	float y;
};