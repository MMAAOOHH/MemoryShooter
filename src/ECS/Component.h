#pragma once

#include "Types.h"

namespace ECS
{
	struct Component
	{
		// 
		Component() : entity_id() {}
		virtual ~Component(){}
		inline const Entity_ID get_id() const { return entity_id; }

	private:
		// Let the manager access private entity_id  
		friend class EntityManager;
		Entity_ID entity_id;
		static int comp_id;
	};
}