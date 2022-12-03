#pragma once

#include "Types.h"

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

		virtual void start(){}
		virtual void update(){}
		virtual void render(){}
		virtual void destroy(){}

	protected:
		friend class SystemManager;
		Entity_Signature signature;
		std::set<Entity_ID> entities;
	};
}
