#pragma once

#include "../System.h"
#include "../Components/Enemy.h"

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

		auto& manager = ECS::ECSManager::get_instance();
		for (auto& id : entities)
		{
			manager.get_component<Enemy>(id).update(delta_time);
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