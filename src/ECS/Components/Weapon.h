#pragma once

#include "../Component.h"
#include "../../ECS/ECS.h"
#include "Physics.h"
#include "Transform.h"
#include "Sprite.h"


struct Projectile : ECS::Component
{
	Vec2 spawn_pos;
	Vec2 direction = { 0,0 };
	float move_speed = 1.f;


	void init()
	{
		auto& manager = ECS::ECSManager::get_instance();
		const auto id = this->entity_id;

		manager.add_component<Transform>(id);
		manager.add_component<RigidBody>(id);
		manager.add_component<Collider>(id);
		manager.add_component<Health>(id);
		manager.add_component<Sprite>(id);

		auto& rb = manager.get_component<RigidBody>(id);
		auto& t = manager.get_component<Transform>(id);
		auto& col = manager.get_component<Collider>(id);

		t.position = spawn_pos;
		t.scale *= 0.01f;
		rb.velocity = direction * move_speed;
		rb.friction = 0.f;
		col.tag = player_projectile;
	}
};

struct Weapon : ECS::Component
{
	float cool_down = 0.5f;

	void shoot(const Vec2 direction)
	{
		auto& manager = ECS::ECSManager::get_instance();
		const auto id = manager.create_entity();
		manager.add_component<Projectile>(id);
		auto& proj = manager.get_component<Projectile>(id);
		proj.direction = direction;
		proj.spawn_pos = manager.get_component<Transform>(entity_id).position;
		proj.init();
	}
};

