#pragma once

#include <SDL/SDL_render.h>

#include "../System.h"
// Is thesce includes the issue, if so why?
#include "../Components/Transform.h"
#include "../Components/Sprite.h"

struct SpriteRenderSystem : ECS::System
{
		SpriteRenderSystem();

		void update(SDL_Renderer* renderer);
};
