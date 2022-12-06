#include "SpriteRenderSystem.h"

#include "../ECS.h"
#include <SDL/SDL_render.h>
#include "../../Common.h"

void SpriteRenderSystem::update(SDL_Renderer* renderer)
{
	if (entities.empty()) return;

	/*
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	int count = 4;
	for (int i = 0; i < count; ++i)
	{
		for (int j = 0; j < count; ++j)
		{
			SDL_Rect rect;
			rect.w = SCREEN_WIDTH / count;
			rect.h = SCREEN_HEIGHT / count;
			rect.x = rect.w * i;
			rect.y = rect.h * j;

			SDL_RenderDrawRect(renderer, &rect);
		}
	}
	*/

	for (auto& entity : entities)
	{
		// Todo: fetch and store components some other way, no need to do it each frame. create map with paired components?
		auto const& transform = ECS::ECSManager::get_instance().get_component<Transform>(entity);
		auto const& sprite = ECS::ECSManager::get_instance().get_component<Sprite>(entity);

		SDL_Color color = sprite.color;
		SDL_Rect rect;
		rect.w = sprite.width;
		rect.h = sprite.height;
		rect.x = transform.position.x - sprite.width * 0.5;
		rect.y = transform.position.y - sprite.height * 0.5;

		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(renderer, &rect);
	}
}
