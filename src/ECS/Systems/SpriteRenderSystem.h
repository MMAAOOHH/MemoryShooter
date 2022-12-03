#pragma once

#include <SDL/SDL_render.h>

#include "../System.h"
// Is thesce includes the issue, if so why?
#include "../Components/Transform.h"
#include "../Components/Sprite.h"

namespace ECS
{
	struct SpriteRenderSystem : System
	{
		SpriteRenderSystem();

		void start() override;
		void update() override;
		void render() override;
		void destroy() override;
	};
}