#include "SpriteRenderSystem.h"

#include "../EntityManager.h"


ECS::SpriteRenderSystem::SpriteRenderSystem()
{
	add_component_signature<Transform>();
	add_component_signature<Sprite>();

	std::cout << "Render Sysem signature: ";
	for (auto const& s : signature)
	{
		std::cout << s << ' ';
	}
	std::cout<< std::endl;
}

void ECS::SpriteRenderSystem::start()
{
}

void ECS::SpriteRenderSystem::update()
{
}

void ECS::SpriteRenderSystem::render()
{
	if (entities.empty()) return;

	for (auto& entity : entities)
	{
		// TODO: how do i solve this? global variable? forward declaration? whats missing?

		auto& transform = EntityManager::get_instance().get_component<Transform>(entity);
		auto& sprite = EntityManager::get_instance().get_component<Sprite>(entity);

		SDL_Color color = sprite.color;

		SDL_Rect rect;

		rect.w = 32;
		rect.h = 32;

		rect.x = transform.position.x;
		rect.y = transform.position.y;

		SDL_SetRenderDrawColor(sprite.renderer, color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(sprite.renderer, &rect);
	}
}

void ECS::SpriteRenderSystem::destroy()
{
}
