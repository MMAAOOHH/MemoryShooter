#include "SpriteRenderSystem.h"

#include "../ECS.h"


SpriteRenderSystem::SpriteRenderSystem()
{

	std::cout << "Render System created" << std::endl;
	//std::cout << "Render Sysem signature: " << signature << std::endl;

}

void SpriteRenderSystem::update(SDL_Renderer* renderer)
{
	if (entities.empty()) return;


	for (auto& entity : entities)
	{
		// Todo: fetch and store components some other way, no need to do it each frame. create map with paired components?
		auto& transform = ECS::ECSManager::get_instance().get_component<Transform>(entity);
		auto& sprite = ECS::ECSManager::get_instance().get_component<Sprite>(entity);

		SDL_Color color = sprite.color;

		SDL_Rect rect;

		rect.w = 32;
		rect.h = 32;

		rect.x = transform.position.x;
		rect.y = transform.position.y;

		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(renderer, &rect);
	}
}
