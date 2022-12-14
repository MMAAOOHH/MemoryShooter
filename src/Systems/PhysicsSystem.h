#pragma once

#include <vector>

#include "../ECS/System.h"
#include "../Components/Physics.h"
#include "../Components/Collider.h"
#include "../Math.h"

struct PhysicsSystem : ECS::System
{
	struct PhysicsData
	{
		Vec2 position;
		Vec2 acceleration;
		Vec2 velocity;
		float friction;
	};

	void init();
	bool validate_data_list_length();
	void get_physics_data();
	void update(float delta_time);

	std::vector<PhysicsData> data_list;
};