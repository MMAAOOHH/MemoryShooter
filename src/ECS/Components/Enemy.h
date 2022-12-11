#pragma once
#include "Collider.h"
#include "Health.h"
#include "Sprite.h"
#include "Transform.h"
#include "Controller.h"
#include "../Component.h"
#include "../ECS.h"


struct EnemyAction
{
	enum Type
	{
		left,
		right,
		up,
		down,
		down_left,
		down_right,
		up_left,
		up_right,
		shoot
	};

	Type action_type;
	float duration;
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

		manager.get_component<Collider>(id).tag = enemy_projectile;
		controller = &manager.get_component<Controller>(id);
		weapon = &manager.get_component<Weapon>(id);
	}

	Weapon* weapon;
	Controller* controller;
	std::vector<EnemyAction> actions;
};
