#pragma once

#include "../System.h"

#include "../Components/Physics.h"
#include "../Components/Collision.h"

struct PhysicsSystem : ECS::System
{
	PhysicsSystem()
	{
		std::cout << "PhysicsSystem created" << std::endl;
	}

	void update(float delta_time);
};