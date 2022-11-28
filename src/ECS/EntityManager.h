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

		void update()
		{
			for (auto& system : registered_systems)
			{
				system.second->update();
			}
		}

		void render()
		{
			for (auto& system : registered_systems)
			{
				system.second->render();
			}
		}

		const Entity_ID add_new_entity()
		{
			const Entity_ID entity = available_entities.front();
			add_entity_signature(entity);
			available_entities.pop();
			entity_count++;
			return entity;
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

		template<typename T, typename... Args>
		void add_component(const Entity_ID entity, Args&&... args)
		{
			assert(entity < MAX_ENTITY_COUNT && "Entidy ID out of range!");
			assert(get_entity_signature(entity)->size() < MAX_COMPONENT_COUNT && "Component count limit reached!");

			T component(std::forward<Args>(args)...);
			component.entity_id = entity;
			get_entity_signature(entity)->insert(component_type<T>());
			get_component_list<T>()->insert(component);
			update_entity_target_systems(entity);

			/*
			const Component_Type_ID comp_type = component_type<T>();
			entities_signatures.at(entity).insert(comp_type);
			attach_entity_to_system(entity);

			*/
		}

		template<typename T>
		void remove_component(const Entity_ID entity)
		{
			assert(entity < MAX_ENTITY_COUNT && "Entidy ID out of range!");
			const Component_Type_ID comp_type = component_type<T>();
			//entities_signatures.at(entity).erase(comp_type);

			get_component_list<T>()->erase(comp_type);
			update_entity_target_systems(entity); // ?
			// Reattach to systems
			//attach_entity_to_system(entity);
		}

		template<typename T>
		T& get_component(const Entity_ID entity)
		{
			assert(entity < MAX_ENTITY_COUNT && "Entidy ID out of range!");
			const Component_Type_ID comp_type = component_type<T>();
			get_component_list<T>()->get(entity);
		}

		template<typename T>
		const bool has_component(const Entity_ID entity)
		{
			assert(entity < MAX_ENTITY_COUNT && "Entidy ID out of range!");
			return (get_entity_signature(entity)->count(component_type<T>()) > 0);
			/*
			const Entity_Signature signature = entities_signatures.at(entity);
			const Component_Type_ID comp_type = component_type<T>();
			return (signature.count(comp_type) > 0);
			*/
		}

		template<typename T>
		void register_system()
		{
			const System_Type_ID sys_type = system_type<T>();
			assert(registered_systems.count(sys_type) == 0 && "System already registered!");
			auto system = std::make_shared<T>();

			// add entity to new system
			for (Entity_ID entity = 0; entity < entity_count; entity++)
			{
				add_entity_to_system(entity, system.get());
			}

			system->start();
			registered_systems[sys_type] = std::move(system);
		}

		template<typename T>
		void unregister_system()
		{
			const System_Type_ID sys_type = system_type<T>();
			assert(registered_systems.count(sys_type) == 0 && "System not registered!");
			registered_systems.erase(sys_type);
		}

	private:

		template<typename T>
		void add_component_list()
		{
			const Component_Type_ID comp_type = component_type<T>();
			assert(components_array.find(comp_type) == components_array.end() && "Component list already exists");
			components_array[comp_type] = std::move(std::make_shared<ComponentList<T>>());
		}

		template<typename T>
		std::shared_ptr<ComponentList<T>> get_component_list()
		{
			const Component_Type_ID comp_type = component_type<T>();

			// Ease of use, lets an entity add a component without having an existing comp list
			if (components_array.count(comp_type) == 0)
			{
				add_component_list<T>();
			}

			return std::static_pointer_cast<ComponentList<T>>(components_array.at(comp_type));
		}
		
		void add_entity_signature(const Entity_ID entity)
		{
			assert(entities_signatures.find(entity) == entities_signatures.end() && "Signature not found!");
			entities_signatures[entity] = std::move(std::make_shared<Entity_Signature>());
		}

		std::shared_ptr<Entity_Signature> get_entity_signature(const Entity_ID entity)
		{
			assert(entities_signatures.find(entity) != entities_signatures.end() && "Signature not found!");
			return entities_signatures.at(entity);
		}
		
		void update_entity_target_systems(const Entity_ID entity)
		{
			for (auto& system : registered_systems)
			{
				add_entity_to_system(entity, system.second.get());
			}
		}

		void add_entity_to_system(const Entity_ID entity, System* system)
		{
			if (belongs_to_system(entity, system->signature))
			{
				system->entities.insert(entity);
			}
			else
			{
				system->entities.erase(entity);
			}
		}
		bool belongs_to_system(const Entity_ID entity, const Entity_Signature& system_signature)
		{
			for (const auto comp_type : system_signature)
			{
				if (get_entity_signature(entity)->count(comp_type) == 0)
				{
					return false;
				}
			}
			return true;
		}

	private:
		Entity_ID entity_count;
		std::queue<Entity_ID> available_entities;
		std::map<Entity_ID, std::shared_ptr<Entity_Signature>> entities_signatures;
		//std::map<Entity_ID, Entity_Signature> entities_signatures;
		std::map<System_Type_ID, std::shared_ptr<System>> registered_systems;
		std::map<Component_Type_ID, std::shared_ptr<IComponentList>> components_array;
	};
}
