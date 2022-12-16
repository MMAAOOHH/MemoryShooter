#pragma once

#include "../ECS/Component.h"
#include "SDL/SDL.h"
#include "../Common.h"

struct Sprite : ECS::Component
{
		SDL_Color color{100, 255, 100, 255};
		float width = DEFAULT_SPRITE_W;
		float height = DEFAULT_SPRITE_H;
};
