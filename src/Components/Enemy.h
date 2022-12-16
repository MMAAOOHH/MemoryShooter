#pragma once

#include "Collider.h"
#include "Health.h"
#include "Sprite.h"
#include "Transform.h"
#include "Controller.h"
#include "Weapon.h"
#include "../ECS/Component.h"
#include "../ECS/ECS.h"
#include "../math.h"

enum class  EnemyState
{
	entry,
	active
};

struct Enemy : ECS::Component
{
	void init()
	{
		auto& manager = ECS::ECSManager::get_instance();
		const auto id = this->entity_id;

		manager.add_component<Controller>(id);
		manager.add_component<Transform>(id);
		manager.add_component<RigidBody>(id);
		manager.add_component<Collider>(id);
		manager.add_component<Sprite>(id);
		manager.add_component<Health>(id);
		manager.add_component<Weapon>(id);

		manager.get_component<Collider>(id).tag = Tag::enemy;
		manager.get_component<Sprite>(id).color = { 255,255,255,255 };
		manager.get_component<RigidBody>(id).friction = 0;
	}

	Vec2 start_position = { 0,0 };
	float time = 0;
	EnemyState state = EnemyState::entry;
};
