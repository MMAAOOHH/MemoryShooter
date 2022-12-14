#pragma once

#include "../Component.h"
#include "../ECS.h"
#include "Physics.h"


struct Controller : ECS::Component
{
	void move(const Vec2 direction)
	{
		auto test = this->entity_id;
		auto& rb = ECS::ECSManager::get_instance().get_component<RigidBody>(this->entity_id);
		rb.acceleration = direction;
	}
};

struct EnemyController : ECS::Component
{
	void move(const Vec2 direction)
	{
		auto test = this->entity_id;
		auto& rb = ECS::ECSManager::get_instance().get_component<RigidBody>(this->entity_id);
		rb.acceleration = direction;
	}
};