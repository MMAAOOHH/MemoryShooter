#pragma once
#include "Collider.h"
#include "Health.h"
#include "Sprite.h"
#include "Transform.h"
#include "Controller.h"
#include "../Component.h"
#include "../ECS.h"

struct Enemy : ECS::Component
{
	float move_speed = 300;

	void init()
	{
		auto& manager = ECS::ECSManager::get_instance();
		const auto id = this->get_id();

		manager.add_component<Controller>(id);
		manager.add_component<Transform>(id);
		manager.add_component<RigidBody>(id);
		manager.add_component<Collider>(id);
		manager.add_component<Sprite>(id);
		manager.add_component<Health>(id);
		manager.add_component<Weapon>(id);

		manager.get_component<Collider>(id).tag = enemy_projectile;

		weapon = &manager.get_component<Weapon>(id);

	}
	float wait = 0.0f;
	void update(const float delta_time)
	{
		Vec2 direction;
		wait += delta_time;
		//std::cout << time << std::endl;
		if (wait >= 2)
		{
			auto& controller = ECS::ECSManager::get_instance().get_component<Controller>(this->get_id());
			direction.x = -1;
			controller.move(direction * move_speed, delta_time);
		}
		if (wait >= 2.2f)
		{
			wait = 0;
		}
	}
	Weapon* weapon;
};
