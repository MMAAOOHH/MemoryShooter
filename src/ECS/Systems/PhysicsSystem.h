#pragma once

#include "../System.h"

#include "../Components/Physics.h"
#include "../Components/Collider.h"

struct PhysicsSystem : ECS::System
{
	PhysicsSystem()
	{
		std::cout << "PhysicsSystem created" << std::endl;
	}

	void update(float delta_time);
};