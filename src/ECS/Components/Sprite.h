#pragma once

#include "../Component.h"
#include "SDL/SDL.h"

namespace ECS
{
	struct Sprite : Component
	{
		Sprite(SDL_Renderer* renderer) : renderer(renderer){}

		SDL_Renderer* renderer;
		SDL_Rect rect = { 0,0, 32, 32 };
		SDL_Color color{100, 255, 100, 255};
	};
}