#pragma once
#include <vector>
#include "Cell.h"
#include <SDL.h>
#include <SDL_image.h>
enum Size
{
	Small,
	Medium,
	Large
};

class Grid
{
public:
	Grid() {};
	Grid(Size size);
	~Grid();
	void Draw(SDL_Renderer &Renderer);
	
	int width;
	int height;
private:
	std::vector<std::vector<Cell>> m_grid;
	SDL_Texture * texture;
	SDL_Rect rect;
};

