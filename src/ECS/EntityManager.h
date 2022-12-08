#pragma once

#include <array>
#include <cassert>
#include <map>
#include <memory>
#include <queue>

#include "Types.h"

namespace ECS
{
	class EntityManager
	{
	public:

		EntityManager(): entity_count(0)
		{
			// "Pool of entities", in a continuous block of memory
			for (Entity entity = 0u; entity < MAX_ENTITY_COUNT; entity++)
			{
				available_entities.push(entity);
			}
		}

		~EntityManager() = default;

		Entity add_new_entity()
		{
			const Entity entity = available_entities.front();
			available_entities.pop();
			entity_count++;
			return entity;
		}

		void destroy_entity(const Entity entity)
		{
			assert(entity < MAX_ENTITY_COUNT && "Entity ID out of range");
			entity_signatures[entity].reset();
			available_entities.push(entity);
			entity_count--;
		}

		void set_entity_signature(const Entity entity, const Signature signature)
		{
			assert(entity < MAX_ENTITY_COUNT && "Entity ID out of range");
			entity_signatures[entity] = signature;
		}

		Signature get_entity_signature(const Entity entity)
		{
			assert(entity < MAX_ENTITY_COUNT && "Entity out of range.");
			return entity_signatures[entity];
		}

	private:
		Entity entity_count;
		std::queue<Entity> available_entities;
		std::array<Signature, MAX_ENTITY_COUNT> entity_signatures;
	};
}