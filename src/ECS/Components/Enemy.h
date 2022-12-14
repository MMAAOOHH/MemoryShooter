#pragma once
#include "Collider.h"
#include "Health.h"
#include "Sprite.h"
#include "Transform.h"
#include "Controller.h"
#include "Weapon.h"
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
		shoot,
		wait
	};

	Type action_type;
	float duration = 1.0f;
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
		manager.get_component<Collider>(id).tag = enemy;

		{
		EnemyAction action;
		action.action_type = EnemyAction::left;
		action.duration = 1;
		actions.push_back(action);
		}

		{
			EnemyAction action;
			action.action_type = EnemyAction::shoot;
			action.duration = 0.05f;
			actions.push_back(action);
		}

		{
			EnemyAction action;
			action.action_type = EnemyAction::right;
			action.duration = 1;
			actions.push_back(action);
		}
		{
			EnemyAction action;
			action.action_type = EnemyAction::shoot;
			action.duration = 0.05f;
			actions.push_back(action);
		}
	}

	bool behaviour_active = false;
	float time = 0;
	int action_index = 0;
	EnemyAction current_action;
	std::vector<EnemyAction> actions;
};
