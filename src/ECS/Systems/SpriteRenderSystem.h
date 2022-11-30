#pragma once

#include <SDL/SDL_render.h>
#include "../System.h"
#include "../Components/Transform.h"
#include "../Components/Sprite.h"


// dont run with errors
namespace ECS
{
	struct SpriteRenderSystem : System
	{
	public:
		SpriteRenderSystem();

		void start() override;
		void update() override;
		void render() override;
		void destroy() override;
	};
}