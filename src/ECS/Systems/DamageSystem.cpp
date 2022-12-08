#pragma once

#include "DamageSystem.h"
#include "../ECS.h"

void DamageSystem::init()
{
}

void DamageSystem::update()
{
	if (entities.empty()) return;

	auto& manager = ECS::ECSManager::get_instance();

	// Store collision components that has collision
	for (const auto& entity : entities)
	{
		auto& c_comp = manager.get_component<Collider>(entity);

		if (c_comp.collision == false) 
			continue;
		collision_components.push_back(c_comp);
	}

	if (collision_components.empty()) return;
	// Handle collision types, get relevant health components
	for (auto& c_comp : collision_components)
	{
		const auto id = c_comp.get_id();
		const auto tag = c_comp.tag;
		const auto collision_from = c_comp.from;

		switch (tag)
		{
			case Collider::player :
				if (collision_from == Collider::player || collision_from == Collider::player_projectile) 
					continue;;
				{
					const auto h_comp = manager.get_component<Health>(id);
					health_components.push_back(h_comp);
				}

				break;

			case Collider::player_projectile:
				if (collision_from == Collider::player || collision_from == Collider::player_projectile)
					continue;
				{
					const auto h_comp = manager.get_component<Health>(id);
					health_components.push_back(h_comp);
				}
				break;

			case Collider::enemy:
				if (collision_from == Collider::enemy || collision_from == Collider::enemy_projectile)
					continue;
				{
					const auto h_comp = manager.get_component<Health>(id);
					health_components.push_back(h_comp);
				}
				break;


			case Collider::enemy_projectile:
				if (collision_from == Collider::enemy || collision_from == Collider::enemy_projectile)
					continue;
				{
					const auto h_comp = manager.get_component<Health>(id);
					health_components.push_back(h_comp);
				}
				break;
		}
	}

	// Deal damage to health components
	for (auto h_comp : health_components)
	{
		h_comp.current_health -= 1;

		if(h_comp.current_health <= 0)
		{
			// Kill entity
			std::cout << "Entity died" << std::endl;
		}
	}

	collision_components.clear();
	health_components.clear();
}
