#include "EnemySystem.h"
#include "../Components/Weapon.h"

void EnemySystem::init()
{
	ECS::Signature signature;
	auto& manager = ECS::ECSManager::get_instance();
	signature.set(manager.get_component_type<Enemy>(), true);

	manager.set_system_signature<EnemySystem>(signature);

	create_grid(4, 8);
}


void EnemySystem::update(const float delta_time)
{
	auto& manager = ECS::ECSManager::get_instance();

	if (entities.empty())
		start_wave();

	// Iterate actions
	for (auto& e : entities)
	{
		auto& enemy = manager.get_component<Enemy>(e);
		manager.get_component<Controller>(e).move(down * 50);
/*
		if (!enemy.behaviour_active) return;

		enemy.current_action = enemy.actions[enemy.action_index];
		auto& action = enemy.current_action;
		enemy.time += delta_time;

		if (enemy.time >= action.duration)
		{
			enemy.action_index++;

			if (enemy.action_index >= (int)enemy.actions.size())
			{
				enemy.action_index = 0;
			}

			enemy.time = 0;
			continue;
		}

		switch (action.action_type)
		{
		case action.left:
			manager.get_component<Controller>(e).move(left * 800);
			break;
		case action.right:
			manager.get_component<Controller>(e).move(right * 800);
			break;
		case action.down:
			manager.get_component<Controller>(e).move(down * 400);
			break;
		case action.up:
			manager.get_component<Controller>(e).move(up * 400);
			break;
		case action.shoot:
			manager.get_component<Weapon>(e).shoot(down * 800);
			break;

		}
	*/
	}
}


void EnemySystem::create_grid(int rows, int cols)
{

	const float width = SCREEN_WIDTH / cols;
	const float height = SCREEN_HEIGHT / 3 / rows;

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			const float x = width * j;
			const float y = height * i;

			Vec2 center;
			center.x = width * 0.5 + x;
			center.y = height * 0.5 + y;

			start_locations.push_back(center);
		}
	}
}

void EnemySystem::start_wave()
{
	wave_timer = 4;
	for (int i = 0; i < 16; ++i)
	{
		Vec2 location = start_locations[i];
		spawn_at_location(location);
	}
}


void EnemySystem::spawn_at_location(Vec2 position)
{
	auto& manager = ECS::ECSManager::get_instance();
	auto id = manager.create_entity();
	manager.add_component<Enemy>(id);

	manager.get_component<Enemy>(id).init();
	auto& t = manager.get_component<Transform>(id);
	t.position = position;
	wave_ids.push_back(id);
}
