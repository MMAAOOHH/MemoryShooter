#pragma once

#include "Types.h"

namespace ECS
{
	class System
	{

	protected:
		friend class SystemManager;
		std::set<Entity> entities;
		//Entity_Signature signature;
	};
}
// OLD
/*	public:
		System() = default;
		virtual ~System() = default;

		void add_entity(const Entity entity)
		{
			entities.insert(entity);
		}
		void remove_entity(const Entity entity)
		{
			entities.erase(entity);
		}
		Entity_Signature get_signature() const
		{
			return signature;
		}

		template<typename T>
		void add_component_signature()
		{
			signature.insert(component_type<T>());
		}


		virtual void start(){}
		virtual void update(){}
		virtual void render(){}
		virtual void destroy(){}*/