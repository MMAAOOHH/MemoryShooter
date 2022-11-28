#pragma once

#include "EntityManager.h"

namespace ECS
{
	class Entity
	{
	public:
		Entity(const Entity_ID entity_id, EntityManager* mgr) : id(entity_id), manager(mgr){}
		~Entity() = default;


		const Entity_ID get_id()
		{
			return id;
		}
		template<typename T, typename... Args>
		void add_component(Args&&... args)
		{
			manager->add_component<T>(id, std::forward<Args>(args)...);
		}

		template<typename T>
		void add_component(T& component)
		{
			manager->add_component<T>(id, component);
		}

		template<typename T>
		T& get_component()
		{
			return manager->get_component<T>(id);
		}

		template<typename T>
		void remove_component()
		{
			manager->remove_component<T>(id);
		}
		template<typename T>
		bool has_component()
		{
			return manager->has_component<T>(id);
		}

	private:
		Entity_ID id;
		EntityManager* manager;
	};
}
