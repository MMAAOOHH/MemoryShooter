#pragma once

#include "../Component.h"
#include "../../ECS/ECS.h"
#include "Transform.h"
#include "Sprite.h"

struct Star : ECS::Component
{
	void init()
	{
		auto& manager = ECS::ECSManager::get_instance();

		manager.add_component<Transform>(this->entity_id);
		manager.add_component<Sprite>(this->entity_id);
	}
};