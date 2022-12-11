#pragma once

#include "DamageSystem.h"
#include "../ECS.h"

void DamageSystem::init()
{
	ECS::Signature signature;
	auto& manager = ECS::ECSManager::get_instance();
	signature.set(manager.get_component_type<Collision>(), true);
	signature.set(manager.get_component_type<Health>(), true);

	manager.set_system_signature<DamageSystem>(signature);
}

void DamageSystem::update()
{
	if (entities.empty()) return;

	auto& manager = ECS::ECSManager::get_instance();

	// Store collision components that has collision
	for (const auto& entity : entities)
	{
		auto& c_comp = manager.get_component<Collision>(entity);

		//std::cout << c_comp.collision << std::endl;

		/*
		if (c_comp.collision == false) 
			continue;
	*/
		collision_components.push_back(c_comp);
	}

	if (collision_components.empty()) return;
	// Handle collision types, get relevant health components
	for (auto& c_comp : collision_components)
	{
		const auto id = c_comp.get_id();
		const auto tag = c_comp.this_tag;
		const auto collision_from = c_comp.from_tag;

		switch (tag)
		{
			case player :
				if (collision_from == player || collision_from == player_projectile) 
					continue;
				{
					const auto h_comp = manager.get_component<Health>(id);
					health_components.push_back(h_comp);
				}

				break;

			case player_projectile:
				if (collision_from == player || collision_from == player_projectile)
					continue;
				{
					const auto h_comp = manager.get_component<Health>(id);
					health_components.push_back(h_comp);
				}
				break;

			case enemy:
				if (collision_from == enemy || collision_from == enemy_projectile)
					continue;
				{
					const auto h_comp = manager.get_component<Health>(id);
					health_components.push_back(h_comp);
				}
				break;


			case enemy_projectile:
				if (collision_from == enemy || collision_from == enemy_projectile)
					continue;
				{
					const auto h_comp = manager.get_component<Health>(id);
					health_components.push_back(h_comp);
				}
				break;
		}
	}

	// Deal damage to health components
	for (auto& h_comp : health_components)
	{
		h_comp.current_health -= 1;

		if(h_comp.current_health <= 0)
		{
			// Kill entity
			std::cout << "Entity died" << std::endl;
			manager.entities_to_remove.push_back(h_comp.get_id());
		}
	}

	// Clear for next update
	collision_components.clear();
	health_components.clear();
}
