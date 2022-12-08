#pragma once
#include <memory>
#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"

namespace ECS
{
	class ECSManager
	{
	public:
		ECSManager()
		{
			entity_manager = std::make_unique<EntityManager>();
			component_manager = std::make_unique<ComponentManager>();
			system_manager = std::make_unique<SystemManager>();
		}

		// delete copy constructor
		ECSManager(const ECSManager&) = delete;

		// TODO: Make unique ptr?
		//singleton
		static ECSManager& get_instance()
		{
			static ECSManager instance;
			return instance;
		}
	
		~ECSManager() = default;

		// Entities
		Entity create_entity()
		{
			return entity_manager->add_new_entity();
		}

		void destroy_entity(const Entity entity)
		{
			entity_manager->destroy_entity(entity);
			component_manager->entity_destroyed(entity);
			system_manager->remove_entity(entity);
		}

		void clean_destroyed()
		{
			for (auto& entity : entities_to_remove)
				destroy_entity(entity);

		}

		// Components
		template<typename T>
		void register_component()
		{
			component_manager->register_component<T>();
		}

		template<typename T>
		void add_component(const Entity entity)
		{
			// Adds the component to managers component list
			component_manager->add_component<T>(entity);

			// Gets signature for entity
			auto signature = entity_manager->get_entity_signature(entity);

			// Updates signature - adds the component to the bit set 
			signature.set(component_manager->get_component_type<T>(), true);

			// Sets new signature for entity
			entity_manager->set_entity_signature(entity, signature);

			// Notifies systems that entity signature was changed
			system_manager->entity_signature_changed(entity, signature);
		}

		template<typename T>
		T& get_component(const Entity entity)
		{
			return component_manager->get_component<T>(entity);
		}

		template<typename T>
		Component_Type get_component_type()
		{
			return component_manager->get_component_type<T>();
		}

		// System
		template<typename T>
		std::shared_ptr<T> register_system()
		{
			return system_manager->register_system<T>();
		}

		template<typename T>
		void set_system_signature(Signature signature)
		{
			system_manager->set_system_signature<T>(signature);
		}

		std::unique_ptr<EntityManager> entity_manager;
		std::unique_ptr<ComponentManager> component_manager;
		std::unique_ptr<SystemManager> system_manager;

		std::vector<Entity> entities_to_remove;
	};
}
