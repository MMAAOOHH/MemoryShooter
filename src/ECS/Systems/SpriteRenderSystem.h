#pragma once

#include <vector>

#include "../System.h"

#include "../Components/Transform.h"
#include "../Components/Sprite.h"

struct RenderData
{
	Vec2 position;
	float width, height;
	SDL_Color color;
};

struct SpriteRenderSystem : ECS::System
{
		SpriteRenderSystem()
		{
			std::cout << "Render System created" << std::endl;
		}

		void init();
		void update(SDL_Renderer* renderer);

private:
		std::vector<RenderData> data_list;
};
