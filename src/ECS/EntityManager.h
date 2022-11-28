#pragma once

#include <map>
#include <memory>
#include <queue>

#include "Types.h"
#include "Component.h"
#include "ComponentList.h"
#include "System.h"

namespace ECS
{
	class EntityManager
	{
	public:
		EntityManager(): entity_count(0)
		{
			for (Entity_ID entity = 0u; entity < MAX_ENTITY_COUNT; entity++)
			{
				available_entities.push(entity);
			}
		}
		~EntityManager()
		{
			
		}

		const Entity_ID add_new_entity()
		{
			const Entity_ID entity_id = available_entities.front();
			available_entities.pop();
			entity_count++;
			return entity_id;
		}

		void destroy_entity(const Entity_ID entity)
		{
			assert(entity < MAX_ENTITY_COUNT && "Entity ID out of range!");
			entities_signatures.erase(entity);

			for (auto& array : components_array)
			{
				array.second->erase(entity);
			}

			for (auto& system : registered_systems)
			{
				system.second->remove_entity(entity);
			}

			entity_count--;
			available_entities.push(entity);
		}
	private:
		Entity_ID entity_count;
		std::queue<Entity_ID> available_entities;
		std::map<Entity_ID, Entity_Signature> entities_signatures;
		std::map<System_Type_ID, std::unique_ptr<System>> registered_systems;
		std::map<Component_Type_ID, std::shared_ptr<IComponentList>> components_array;
	};
}
