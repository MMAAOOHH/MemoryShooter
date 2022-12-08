#pragma once

#include "../System.h"
#include "../Components/Delete.h"
#include "../ECS.h"

struct Collider;

struct DeleteSystem : ECS::System
{
	void init()
	{
		// Set system signature
		auto& manager = ECS::ECSManager::get_instance();
		ECS::Signature signature;
		signature.set(manager.get_component_type<Delete>(), true);

		manager.set_system_signature<DeleteSystem>(signature);
	}

	void update()
	{
		if (entities.empty()) return;
		for (const auto& entity : entities)
		{
			auto id = entity;
			ECS::ECSManager::get_instance().destroy_entity(id);
		}
	}
};
