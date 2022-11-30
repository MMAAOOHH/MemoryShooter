#include "SpriteRenderSystem.h"

#include "../EntityManager.h"

ECS::SpriteRenderSystem::SpriteRenderSystem()
{
	add_component_signature<Transform>();
	add_component_signature<Sprite>();
}

void ECS::SpriteRenderSystem::start()
{
	System::start();
}

void ECS::SpriteRenderSystem::update()
{
	System::update();
}

void ECS::SpriteRenderSystem::render()
{
	for (auto& entity : entities)
	{
		// TODO: how do i solve this? global variable? forward declaration? whats missing?

		auto& transform = EntityManager::get_instance().get_component<Transform>(entity);
		auto& sprite = EntityManager::get_instance().get_component<Sprite>(entity);

		SDL_Rect rect = sprite.rect;
		SDL_Color color = sprite.color;
		SDL_Renderer* renderer = sprite.renderer;

		rect.x = transform.position.x;
		rect.y = transform.position.y;

		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(renderer, &rect);
	}
}

void ECS::SpriteRenderSystem::destroy()
{
	System::destroy();
}
