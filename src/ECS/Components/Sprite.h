#pragma once

#include "../Component.h"
#include "SDL/SDL.h"

namespace ECS
{
	struct Sprite : Component
	{
		Sprite(SDL_Renderer* rnd) : renderer(rnd){}

		SDL_Renderer* renderer;
		SDL_Rect rect = { 0,0, 16, 16 };
		SDL_Color color{100, 255, 100, 255};
		
	};
}