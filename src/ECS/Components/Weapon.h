#pragma once

#include "../Component.h"
#include "../../ECS/ECS.h"
#include "Physics.h"
#include "Transform.h"
#include "Sprite.h"


struct Bullet : ECS::Component
{
	Vec2 direction;
	float speed;

	void init()
	{
		auto& manager = ECS::ECSManager::get_instance();
		manager.add_component<Transform>(this->get_id());
		manager.add_component<Sprite>(this->get_id());
		manager.add_component<RigidBody>(this->get_id());
		manager.add_component<Collider>(this->get_id());

		manager.get_component<Sprite>(this->get_id()).width = 4;
		manager.get_component<Sprite>(this->get_id()).height = 4;

		manager.get_component<RigidBody>(this->get_id()).friction = 0.f;
		manager.get_component<RigidBody>(this->get_id()).velocity = direction * speed;
	}
};

struct Weapon : ECS::Component
{

	float cool_down = 0.5f;

	void shoot(Vec2 direction)
	{
		auto& manager = ECS::ECSManager::get_instance();
		auto bullet = manager.create_entity();
		manager.add_component<Bullet>(bullet);
		manager.get_component<Bullet>(bullet).init();

		auto const spawn_pos = manager.get_component<Transform>(this->get_id()).position;
		manager.get_component<Transform>(bullet).position = spawn_pos;
		
	}
};

