#pragma once

#include "PhysicsSystem.h"
#include "../ECS.h"
#include "../Components/Transform.h"
#include "../Components/Physics.h"

const float GRATIVTY = 0.00001f;

void PhysicsSystem::update(float delta_time)
{
	if (entities.empty()) 
		return;

	for (auto& entity : entities)
	{
		auto& transform = ECS::ECSManager::get_instance().get_component<Transform>(entity);
		auto& rigid_body = ECS::ECSManager::get_instance().get_component<RigidBody>(entity);

		transform.position += rigid_body.velocity * delta_time;

		if (!rigid_body.use_gravity)
			return;

		rigid_body.velocity.y += GRATIVTY * delta_time;
	}
}
