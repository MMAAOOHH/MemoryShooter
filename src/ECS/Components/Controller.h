#pragma once

#include "../Component.h"
#include "../ECS.h"
#include "Physics.h"


struct Controller : ECS::Component
{
	void init()
	{
		//ECS::ECSManager::get_instance().add_component<RigidBody>(this->get_id());
	}

	void move(const Vec2 direction, const float delta_time)
	{
		auto& rb = ECS::ECSManager::get_instance().get_component<RigidBody>(this->entity_id);
		rb.acceleration = direction;
		//rb.add_force(direction, delta_time);
	}
};
