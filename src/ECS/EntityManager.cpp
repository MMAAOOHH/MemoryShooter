#include "EntityManager.h"

void ECS::EntityManager::update()
{
	for (auto& system : registered_systems)
	{
		system.second->update();
	}
}

void ECS::EntityManager::render()
{
	for (auto& system : registered_systems)
	{
		system.second->render();
	}
}

const ECS::Entity_ID ECS::EntityManager::add_new_entity()
{
	const Entity_ID entity = available_entities.front();
	add_entity_signature(entity);
	available_entities.pop();
	entity_count++;
	return entity;
}

void ECS::EntityManager::destroy_entity(const Entity_ID entity)
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

void ECS::EntityManager::add_entity_signature(const Entity_ID entity)
{
	assert(entities_signatures.find(entity) == entities_signatures.end() && "Signature not found!");
	entities_signatures[entity] = std::move(std::make_shared<Entity_Signature>());
}

std::shared_ptr<ECS::Entity_Signature> ECS::EntityManager::get_entity_signature(const Entity_ID entity)
{
	assert(entities_signatures.find(entity) != entities_signatures.end() && "Signature not found!");
	return entities_signatures.at(entity);
}

void ECS::EntityManager::update_entity_target_systems(const Entity_ID entity)
{
	for (auto& system : registered_systems)
	{
		add_entity_to_system(entity, system.second.get());
	}
}

void ECS::EntityManager::add_entity_to_system(const Entity_ID entity, System* system)
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
bool ECS::EntityManager::belongs_to_system(const Entity_ID entity, const Entity_Signature& system_signature)
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