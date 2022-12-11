#pragma once

#include <vector>

#include "../System.h"
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

	std::vector<Collision> collision_components;
	std::vector<Health> health_components;
};