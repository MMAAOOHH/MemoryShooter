#pragma once

#include "../ECS/Component.h"
#include "../ECS/ECS.h"
#include "Transform.h"
#include "Sprite.h"

struct Star : ECS::Component
{
	void init()
	{
		auto& manager = ECS::World::get_instance();

		manager.add_component<Transform>(this->entity_id);
		manager.add_component<Sprite>(this->entity_id);
	}
};