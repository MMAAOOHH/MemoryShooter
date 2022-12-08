#pragma once

#include <unordered_map>

#include "Types.h"
#include "ComponentList.h"
#include "Component.h"

namespace ECS
{
	class ComponentManager
	{

	public:
		template<typename T>
		void register_component()
		{
			static_assert((std::is_base_of<Component, T>::value && !std::is_same<Component, T>::value), "INVALID TEMPLATE TYPE");

			const char* type = typeid(T).name();
			assert(components_array.find(type) == components_array.end() && "Component type already registered");

			// Register component type
			component_types.insert({ type, next_type_id });
			// Create  component list
			components_array.insert({ type, std::make_shared<ComponentList<T>>() });

			next_type_id++;
		}

		template<typename T, typename... Args>
		void add_component(const Entity entity, Args&&... args)
		{
			assert(entity < MAX_ENTITY_COUNT && "Entidy ID out of range!");

			T component(std::forward<Args>(args)...);
			// TODO: Remove after we change how we deal with components. 
			component.entity_id = entity;

			get_component_list<T>()->insert(component);
		}

		template<typename T>
		void remove_component(const Entity entity)
		{
			assert(entity < MAX_ENTITY_COUNT && "Entidy ID out of range!");
			get_component_list<T>()->erase(entity);
		}

		template<typename T>
		T& get_component(const Entity entity)
		{
			assert(entity < MAX_ENTITY_COUNT && "Entidy ID out of range!");
			return get_component_list<T>()->get(entity);
		}

		template<typename T>
		Component_Type get_component_type()
		{
			const char* type = typeid(T).name();
			assert(component_types.find(type) != component_types.end() && "Component not registered");
			return component_types[type];
		}

		void entity_destroyed(Entity entity)
		{
			for (auto const& pair : components_array)
			{
				auto const& component = pair.second;
				// Todo: make more memory oriented, see comments in ComponentList.h
				component->erase(entity);
			}
		}


	private:

		template<typename T>
		std::shared_ptr<ComponentList<T>> get_component_list()
		{
			const char* type = typeid(T).name();
			assert(component_types.find(type) != component_types.end() && "Component not registered");
			return std::static_pointer_cast<ComponentList<T>>(components_array.at(type));
		}

		std::unordered_map<const char*, Component_Type> component_types;
		std::unordered_map<const char*, std::shared_ptr<IComponentList>> components_array;
		Component_Type next_type_id = 0u;
	};
}