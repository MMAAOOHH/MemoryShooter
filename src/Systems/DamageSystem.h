#pragma once

#include <vector>

#include "../ECS/System.h"
#include "../Components/Health.h"
#include "../Components/Collider.h"

struct DamageSystem : ECS::System
{
	DamageSystem()
	{
		std::cout << "DamageSystem created" << std::endl;
	}

	void init();
	void update();
	void damage_player(ECS::Entity id);

	std::vector<Collision> collision_components;
	std::vector<Health> health_components;
	std::vector<ECS::Entity> to_damage;
};