#pragma once

#include <map>
#include <memory>
#include <queue>

#include "Types.h"
#include "ComponentList.h"
#include "System.h"

namespace ECS
{
	class EntityManager
	{
	private:

		EntityManager(): entity_count(0)
		{
			// "Pool of entities", in a continuous block of memory
			for (Entity_ID entity = 0u; entity < MAX_ENTITY_COUNT; entity++)
			{
				available_entities.push(entity);
			}
		}

	public:

		// delete copy constructor
		EntityManager(const EntityManager&) = delete;

		//singleton
		static EntityManager& get_instance()
		{
			static EntityManager instance;
			return instance;
		}

		~EntityManager(){}

		void update();
		void render();
		const Entity_ID add_new_entity();
		void destroy_entity(const Entity_ID entity);

	private:
		void add_entity_signature(const Entity_ID entity);
		std::shared_ptr<Entity_Signature> get_entity_signature(const Entity_ID entity);
		void update_entity_target_systems(const Entity_ID entity);
		void add_entity_to_system(const Entity_ID entity, System* system);
		bool belongs_to_system(const Entity_ID entity, const Entity_Signature& system_signature);
		

#pragma region Templates

	public:
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
			// Reattach to systems
			update_entity_target_systems(entity); // ?
		}

		// TODO: should this be static?
		template<typename T>
		T& get_component(const Entity_ID entity)
		{
			assert(entity < MAX_ENTITY_COUNT && "Entidy ID out of range!");
			const Component_Type_ID comp_type = component_type<T>();
			return get_component_list<T>()->get(entity);
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

			// Lets an entity add a component without having an existing comp list
			if (components_array.count(comp_type) == 0)
			{
				add_component_list<T>();
			}

			return std::static_pointer_cast<ComponentList<T>>(components_array.at(comp_type));
		}

#pragma endregion

	private:
		Entity_ID entity_count;
		std::queue<Entity_ID> available_entities;
		std::map<Entity_ID, std::shared_ptr<Entity_Signature>> entities_signatures;
		//std::map<Entity_ID, Entity_Signature> entities_signatures;
		std::map<System_Type_ID, std::shared_ptr<System>> registered_systems;
		std::map<Component_Type_ID, std::shared_ptr<IComponentList>> components_array;
	};
}
