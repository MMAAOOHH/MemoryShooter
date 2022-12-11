#pragma once

#include "../System.h"
#include "../Components/Enemy.h"

struct Direction
{
	Vec2 left = { -1, 0 };
	Vec2 right = { 1, 0 };
	Vec2 up = { 0, -1 };
	Vec2 down = { 0, 1 };
	Vec2 down_left = { -1, 1 };
	Vec2 down_right = { 1, 1 };
	Vec2 up_left = { -1, -1 };
	Vec2 up_right = { 1, -1 };
};

struct EnemySystem : ECS::System
{
	EnemySystem()
	{
		std::cout << "EnemySystem created" << std::endl;
	}

	void init()
	{
		ECS::Signature signature;
		auto& manager = ECS::ECSManager::get_instance();
		signature.set(manager.get_component_type<Enemy>(), true);

		manager.set_system_signature<EnemySystem>(signature);
	}

	void update(const float delta_time)
	{
		time += delta_time;
		for (auto& enemy : enemies)
		{
			for (const auto& action : enemy.actions)
			{
				if (time >= action.duration)
					continue;

				switch (action.action_type)
				{
				case action.left :
					//enemy.controller->move(Direction.left)
					break;
				case action.right :
					//enemy.controller->move(Direction.right)
					break;
				case action.down :
					//enemy.controller->move(Direction.down)
					break;
				case action.up :
					//enemy.controller->move(Direction.up)
					break;
				case action.down_left :
					//enemy.controller->move(Direction.down_left)
					break;
				case action.down_right :
					//enemy.controller->move(Direction.down_right)
					break;
				case action.up_left :
					//enemy.controller->move(Direction.up_left)
					break;
				case action.up_right :
					//enemy.controller->move(Direction.up_right)
					break;
				case action.shoot :
					//enemy.weapon->shoot({ 0, 1 });
					break;
				
				}
			}
		}
	}

	void spawn_at_location(Vec2 position)
	{
		auto& manager = ECS::ECSManager::get_instance();
		auto e = manager.create_entity();
		manager.add_component<Enemy>(e);
		manager.get_component<Transform>(e).position = position;
	}

	int get_enemy_count()
	{
		return entities.size();
	}

	int current_wave_index;
	int current_wave_enemy_count;
	std::vector<Enemy> enemies;
	float time;
};