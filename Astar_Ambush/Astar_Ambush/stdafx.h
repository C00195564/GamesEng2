#pragma once


#include <vector>
#include <cmath>
#include <thread>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "CD_Vector2f.h"

enum Size
{
	Small = 30,
	Medium = 100,
	Large = 1000
};

#define FRAMES_PER_SECOND 60
#define SCREEN_TICKS_PER_FRAME 1000 / FRAMES_PER_SECOND

#define PIXELSIZE_SMALL 31
#define PIXELSIZE_MEDIUM 11
#define PIXELSIZE_LARGE 3

#define THREAD_NUM std::thread::hardware_concurrency()