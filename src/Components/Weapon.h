#pragma once

#include "../ECS/Component.h"
#include "../ECS/ECS.h"
#include "Physics.h"
#include "Transform.h"
#include "Sprite.h"


struct Projectile : ECS::Component
{
	Vec2 spawn_pos = { 0,0 };
	Vec2 direction = { 0,0 };
	Tag tag;

	void init()
	{
		auto& manager = ECS::World::get_instance();
		auto& id = this->entity_id;

		manager.add_component<Transform>(id);
		manager.add_component<RigidBody>(id);
		manager.add_component<Collider>(id);
		manager.add_component<Health>(id);
		manager.add_component<Sprite>(id);

		auto& rb = manager.get_component<RigidBody>(id);
		auto& t = manager.get_component<Transform>(id);
		 
		t.position = spawn_pos;
		rb.velocity = direction;
		rb.friction = 0.f;

		manager.get_component<Collider>(id).tag = tag;
		if (tag == Tag::enemy_projectile)
		{
			t.scale *= 0.4f;
			manager.get_component<Sprite>(id).color = { 255,255 ,255,255 };
		}
		else
		{
			t.scale *= 0.2f;
		}
	}
};


struct Weapon : ECS::Component
{
	void shoot(const Vec2 direction, const Tag tag)
	{
		auto& manager = ECS::World::get_instance();
		const auto& id = manager.create_entity();

		manager.add_component<Projectile>(id);
		auto& proj = manager.get_component<Projectile>(id);

		proj.direction = direction;
		proj.spawn_pos = manager.get_component<Transform>(entity_id).position;
		proj.tag = tag;
		proj.init();
	}
};
