#pragma once

#include "../System.h"

#include "../Components/Transform.h"
#include "../Components/Sprite.h"

struct SpriteRenderSystem : ECS::System
{
		SpriteRenderSystem()
		{
			std::cout << "Render System created" << std::endl;
		}

		void update(SDL_Renderer* renderer);
};
