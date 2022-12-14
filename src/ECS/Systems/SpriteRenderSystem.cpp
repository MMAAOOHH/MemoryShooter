#include "SpriteRenderSystem.h"

#include "../ECS.h"
#include <SDL/SDL_render.h>
#include "../../Common.h"

void SpriteRenderSystem::init()
{
	auto& manager = ECS::ECSManager::get_instance();
	ECS::Signature signature;
	signature.set(manager.get_component_type<Transform>(), true);
	signature.set(manager.get_component_type<Sprite>(), true);

	manager.set_system_signature<SpriteRenderSystem>(signature);
}

void SpriteRenderSystem::update(SDL_Renderer* renderer)
{
	if (entities.empty()) return;

	/*
	int size = 4;
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			SDL_Rect cell;
			float width = SCREEN_WIDTH / size;
			float height = SCREEN_WIDTH / size;

			float x = width * i;
			float y = height * j;

			Vec2 center;
			cell.x = x;
			cell.y = y;

			cell.w = width;
			cell.h = height;

			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderDrawRect(renderer, &cell);
		}
	}
	*/

	
	for (auto& entity : entities)
	{
		RenderData data;
		// Todo: fetch and store components some other way, no need to do it each frame. create map with paired components?
		auto const& transform = ECS::ECSManager::get_instance().get_component<Transform>(entity);
		auto const& sprite = ECS::ECSManager::get_instance().get_component<Sprite>(entity);

		data.position = transform.position;
		data.width = sprite.width;
		data.height = sprite.height;
		data.color = sprite.color;
		data_list.push_back(data);
	}

	for (auto& data : data_list)
	{
		SDL_Rect rect;
		rect.w = data.width;
		rect.h = data.height;
		rect.x = data.position.x - data.width * 0.5;
		rect.y = data.position.y - data.height * 0.5;
		SDL_SetRenderDrawColor(renderer, data.color.r, data.color.g, data.color.b, data.color.a);
		SDL_RenderFillRect(renderer, &rect);
	}
	data_list.clear();
}
