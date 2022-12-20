#pragma once

#include "DamageSystem.h"
#include "../ECS/ECS.h"
#include "../Components/Health.h"
#include "../Components/Collider.h"
#include "../Components/Enemy.h"

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
					damage_player(id);
				break;

			case Tag::enemy:
				if (collision_from == Tag::player_projectile || collision_from == Tag::player)
					to_damage.push_back(id);
				break;

			case Tag::player_projectile:
				if (collision_from == Tag::enemy || collision_from == Tag::enemy_projectile)
					to_damage.push_back(id);
				break;

			case Tag::enemy_projectile:
				if (collision_from == Tag::player || collision_from == Tag::player_projectile)
					to_damage.push_back(id);
				break;
		}
	}

	// Deal damage
	for (auto& id : to_damage)
	{
		auto& h_comp = manager.get_component<Health>(id);
		h_comp.current_health -= 1;

		if (h_comp.current_health <= 0)
		{
			manager.entities_to_remove.push_back(id);
		}
	}

	// Clear for next update
	collision_components.clear();
	health_components.clear();
	to_damage.clear();
}

void DamageSystem::damage_player(ECS::Entity id)
{
	auto& manager = ECS::ECSManager::get_instance();
	auto& h_comp = manager.get_component<Health>(id);
	h_comp.current_health -= 1;

	if (h_comp.current_health <= 0)
	{
		// player died
		std::cout << "Player died" << std::endl;
	}
}
