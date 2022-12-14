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

struct PlayerController : ECS::Component
{
	void init()
	{
		auto& manager = ECS::ECSManager::get_instance();

		manager.add_component<Controller>(this->entity_id);
		manager.add_component<Transform>(this->entity_id);
		manager.add_component<Sprite>(this->entity_id);
		manager.add_component<Collider>(this->entity_id);
		manager.add_component<RigidBody>(this->entity_id);
		manager.add_component<Weapon>(this->entity_id);
		manager.add_component<Health>(this->entity_id);

		manager.get_component<Collider>(this->entity_id).tag = player;
		manager.get_component<Health>(this->entity_id).current_health = 10;

	}

	float weapon_wait = 0.5f;
	float move_speed = 2000.f;

	void update(const float delta_time)
	{
		Vec2 direction;
		if ((keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP])) 
			direction.y = -1;

		if ((keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN]))
			direction.y = 1;

		if ((keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT]))
			direction.x = -1;

		if ((keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]))
			direction.x = 1;

		auto& rb = ECS::ECSManager::get_instance().get_component<RigidBody>(this->entity_id);
		auto& t = ECS::ECSManager::get_instance().get_component<Transform>(this->entity_id);

		// TODO: make better
		// Screen wrap
		if (t.position.x < 0) t.position.x = SCREEN_WIDTH;
		if (t.position.x > SCREEN_WIDTH) t.position.x = 0;
		// Bot and top border block
		if (t.position.y < 0) t.position.y = 0;
		if (t.position.y > SCREEN_HEIGHT) t.position.y = SCREEN_HEIGHT;


		rb.acceleration = direction * move_speed;

		
		if ((keys[SDL_SCANCODE_SPACE]))
		{
			weapon_wait += delta_time;
			if (weapon_wait > 0.1f)
			{
				ECS::ECSManager::get_instance().get_component<Weapon>(this->entity_id).shoot({0, -700}, player_projectile);
				weapon_wait = 0;
			}
		}
	}

	 Transform* transform;
};
