#pragma once
#include "Collider.h"
#include "Health.h"
#include "Sprite.h"
#include "Transform.h"
#include "../Component.h"
#include "../ECS.h"

struct Enemy : ECS::Component
{
	float move_speed = 2000.f;

	void init()
	{
		auto& manager = ECS::ECSManager::get_instance();

		manager.add_component<Transform>(this->get_id());
		manager.add_component<Sprite>(this->get_id());
		manager.add_component<Collider>(this->get_id());
		manager.add_component<Health>(this->get_id());

		manager.get_component<Collider>(this->get_id()).tag = Collider::enemy_projectile;
	}
	void update(const float delta_time){}
};
