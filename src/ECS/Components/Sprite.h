#pragma once

#include "../Component.h"
#include "SDL/SDL.h"
#include "../../Common.h"

struct Sprite : ECS::Component
{
		SDL_Color color{100, 255, 100, 255};
		int width = DEFAULT_SPRITE_W;
		int height = DEFAULT_SPRITE_H;
};
