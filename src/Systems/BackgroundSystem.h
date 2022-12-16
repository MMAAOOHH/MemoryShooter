#pragma once

#include "../ECS/ECS.h"
#include "../ECS/System.h"
#include "../ECS/Types.h"
#include "../Components/Star.h"

struct BackgroundSystem : ECS::System
{
	void init()
	{
		auto& manager = ECS::ECSManager::get_instance();
		ECS::Signature signature;
		signature.set(manager.get_component_type<Star>(), true);
		manager.set_system_signature<BackgroundSystem>(signature);

		// create stars
		int count = 100;
		srand(time(NULL));
		rand();
		for (int i = 0; i < count; ++i)
		{
			int x = rand() % SCREEN_WIDTH;
			int y = rand() % SCREEN_HEIGHT;

			//int x = SCREEN_WIDTH * 0.5;
			//int y = SCREEN_HEIGHT * 0.5;

			SDL_Color rand_color;
			rand_color.r = rand() % 255;
			rand_color.g = rand() % 255;
			rand_color.b = rand() % 255;
			rand_color.a = 255;

			const auto e = ECS::ECSManager::get_instance().create_entity();

			manager.add_component<Star>(e);
			manager.get_component<Star>(e).init();

			manager.get_component<Sprite>(e).color = rand_color;

			auto& transform = manager.get_component<Transform>(e);
			transform.position = { (float)x, (float)y };
			transform.scale = 0.05f;
		}
	}

	void update(float delta_time)
	{
		for (auto& id : entities)
		{
			auto& transform = ECS::ECSManager::get_instance().get_component<Transform>(id);

			transform.position.y += 100 * delta_time;
			if (transform.position.y > SCREEN_HEIGHT)
			{
				transform.position.y = -10;
			}
		}
	}
	std::vector<Transform> transforms;
};