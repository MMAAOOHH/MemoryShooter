#pragma once

#include <SDL/SDL_scancode.h>

#include "../Component.h"
#include "../ECS.h"
#include "Controller.h"
#include "Transform.h"
#include "Sprite.h"
#include "Physics.h"

#include "..//../Common.h"

struct Player : ECS::Component
{
	float move_speed = 2000.f;

	void init()
	{
		ECS::ECSManager::get_instance().add_component<Controller>(this->get_id());
		ECS::ECSManager::get_instance().add_component<Transform>(this->get_id());
		ECS::ECSManager::get_instance().add_component<Sprite>(this->get_id());
		ECS::ECSManager::get_instance().add_component<RigidBody>(this->get_id());
	}

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
	}
};
