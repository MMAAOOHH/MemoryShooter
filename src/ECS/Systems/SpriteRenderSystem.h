#pragma once

#include <SDL/SDL_render.h>

#include "../System.h"
#include "../Components/Transform.h"
#include "../Components/Sprite.h"
#include "../Components/Collision.h"


// dont run with errors
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