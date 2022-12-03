#pragma once

#include "../Component.h"
#include "SDL/SDL.h"


struct Sprite : ECS::Component
{
		SDL_Rect rect = { 0,0, 16, 16 };
		SDL_Color color{100, 255, 100, 255};
};
