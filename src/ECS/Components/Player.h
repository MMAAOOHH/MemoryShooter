#pragma once

#include <SDL/SDL_scancode.h>

#include "../Component.h"
#include "../ECS.h"
#include "Controller.h"
#include "Health.h"
#include "Transform.h"
#include "Sprite.h"
#include "Physics.h"
#include "Weapon.h"

#include "..//../Common.h"

struct Player : ECS::Component
{
	float move_speed = 2000.f;

	void init()
	{
		auto& manager = ECS::ECSManager::get_instance();

		manager.add_component<Controller>(this->get_id());
		manager.add_component<Transform>(this->get_id());
		manager.add_component<Sprite>(this->get_id());
		manager.add_component<Collider>(this->get_id());
		manager.add_component<RigidBody>(this->get_id());
		manager.add_component<Weapon>(this->get_id());
		manager.add_component<Health>(this->get_id());

		manager.get_component<Collider>(this->get_id()).tag = Collider::player;
	}

	float weapon_wait = 0.5f;

	void update(const float delta_time)
	{
		Vec2 direction;

		if ((keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP]))
		{
			direction.y = -1;
		}

		if ((keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN]))
		{
			direction.y = 1;
		}

		if ((keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT]))
		{
			direction.x = -1;
		}

		if ((keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]))
		{
			direction.x = 1;
		}

		auto& controller = ECS::ECSManager::get_instance().get_component<Controller>(this->get_id());
		controller.move(direction * move_speed, delta_time);

		if ((keys[SDL_SCANCODE_SPACE]))
		{
			weapon_wait += delta_time;
			if (weapon_wait > 0.1f)
			{
				ECS::ECSManager::get_instance().get_component<Weapon>(this->get_id()).shoot({0, 1});
				weapon_wait = 0;
			}
		}
	}
};
