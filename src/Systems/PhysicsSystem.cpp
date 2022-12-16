#include "PhysicsSystem.h"
#include "../ECS/ECS.h"
#include "../Components/Transform.h"
#include "../Components/Physics.h"
#include "../Common.h"


//const float GRATIVTY = 0.00002f;

void PhysicsSystem::init()
{
	auto& manager = ECS::ECSManager::get_instance();
	ECS::Signature signature;
	signature.set(manager.get_component_type<Transform>(), true);
	signature.set(manager.get_component_type<RigidBody>(), true);

	manager.set_system_signature<PhysicsSystem>(signature);
}



void PhysicsSystem::update(const float delta_time) 
{
	if (entities.empty()) return;
	auto& manager = ECS::ECSManager::get_instance();

	for (auto& id : entities)
	{
		auto& transform = manager.get_component<Transform>(id);
		auto& rb = manager.get_component<RigidBody>(id);

		rb.acceleration += rb.velocity * -rb.friction;
		transform.position += rb.velocity * delta_time + rb.acceleration * 0.5 * delta_time * delta_time;
		rb.velocity += rb.acceleration * delta_time;
		rb.acceleration = { 0,0 };

		// Checks if entity is outside of allowed game area
		if (transform.position.y > SCREEN_HEIGHT + 50 || transform.position.y < -50 || 
			transform.position.x > SCREEN_WIDTH + 200 || transform.position.x < -200)
			manager.entities_to_remove.push_back(id);
	}
}


bool PhysicsSystem::validate_data_list_length()
{
	return entities.size() == data_list.size();
}

void PhysicsSystem::get_physics_data()
{
	for (auto& id : entities)
	{
		PhysicsData data;

		auto& transform = ECS::ECSManager::get_instance().get_component<Transform>(id);
		auto& rb = ECS::ECSManager::get_instance().get_component<RigidBody>(id);

		data.velocity = rb.velocity;
		data.acceleration = rb.acceleration;
		data.position = transform.position;

		data_list.push_back(data);
	}
}