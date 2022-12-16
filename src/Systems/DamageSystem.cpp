#pragma once

#include "DamageSystem.h"
#include "../ECS/ECS.h"

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

	// Get collision components
	for (const auto& entity : entities)
	{
		auto& c_comp = manager.get_component<Collision>(entity);
		collision_components.push_back(c_comp);
	}

	// Handle collision types
	for (const auto& c_comp : collision_components)
	{
		auto& id = c_comp.entity_id;
		auto& tag = c_comp.this_tag;
		auto& collision_from = c_comp.from_tag;

		switch (tag)
		{
			case Tag::player :
				if (collision_from == Tag::enemy || collision_from == Tag::enemy_projectile) 
				{
					auto& h_comp = manager.get_component<Health>(id);
					health_components.push_back(h_comp);
				}
				break;

		case Tag::enemy:
				if (collision_from == Tag::player_projectile || collision_from == Tag::player)
				{
					auto& h_comp = manager.get_component<Health>(id);
					health_components.push_back(h_comp);
				}
				break;

			case Tag::player_projectile:
				if (collision_from == Tag::enemy || collision_from == Tag::enemy_projectile)
				{
					auto& h_comp = manager.get_component<Health>(id);
					health_components.push_back(h_comp);
				}
				break;


			case Tag::enemy_projectile:
				if (collision_from == Tag::player || collision_from == Tag::player_projectile)
				{
					auto& h_comp = manager.get_component<Health>(id);
					health_components.push_back(h_comp);
				}
				break;
		}
	}

	// Deal damage
	for (auto& h_comp : health_components)
	{
		h_comp.current_health -= 1;

		if(h_comp.current_health <= 0)
		{
			manager.entities_to_remove.push_back(h_comp.entity_id);
		}
	}

	// Clear for next update
	collision_components.clear();
	health_components.clear();
}
