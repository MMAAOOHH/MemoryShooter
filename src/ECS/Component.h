#pragma once

#include "Types.h"

namespace ECS
{
	struct Component
	{
		// 
		Component() : entity_id() {}
		virtual ~Component(){}
		inline const Entity get_id() const { return entity_id; }

	//private:
	//	// Let the manager access and set private entity_id  
	//	friend class ComponentManager;
		Entity entity_id;
	};
}