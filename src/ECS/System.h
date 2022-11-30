#pragma once

#include "Types.h"
#include <iostream>

namespace ECS
{
	class System
	{
	public:
		System() = default;
		virtual ~System() = default;

		void add_entity(const Entity_ID entity);

		void remove_entity(const Entity_ID entity);

		Entity_Signature get_signature() const;

		template<typename T>
		void add_component_signature()
		{
			signature.insert(component_type<T>());
		}

		virtual void start() {}
		virtual void update()
		{
			/*
			std::cout << "System " << &signature << " has entity: ";
			for (auto i : entities)
			{
				std::cout << i << " ";
			}
			std::cout << std::endl;
			*/
		}
		virtual void render(){}
		virtual void destroy() {}

	protected:
		friend class EntityManager;
		Entity_Signature signature;
		std::set<Entity_ID> entities;
	};
}
