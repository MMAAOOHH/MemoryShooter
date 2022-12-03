#pragma once

#include "AABBSystem.h"

#include "../ECS.h"
#include "../Components/Transform.h"
#include "../Components/Collision.h"

AABBSystem::AABBSystem()
{
	ECS::Signature signature;
	signature.set(ECS::ECSManager::get_instance().get_component_type<Transform>(), true);
	signature.set(ECS::ECSManager::get_instance().get_component_type<Collision>(), true);

	ECS::ECSManager::get_instance().set_system_signature<AABBSystem>(signature);

	std::cout << "AABBSystem created" << std::endl;
	std::cout << "AABBSystem signature: " << signature << std::endl;
}



void AABBSystem::update()
{
	
	// make AABB box and store for each entry, kinda bad cause we already have our list but whatever

	if (entities.empty()) return;

	/*
	for (auto& entity : entities)
	{
		auto& transform = EntityManager::get_instance().get_component<Transform>(entity);
		//AABB box = make_from_position_size(transform.position.x, transform.position.y, 16, 16);
		//aabb_list.push_back(box);
	}
	*/
	
	// check collision
	/*
	if(!aabb_list.empty())
	{
		for (int i = 0; i < aabb_list.size(); ++i)
		{
			for (int j = 0; j < aabb_list.size(); ++i)
			{
				if (i == j) continue;
				if (aabb_intersect(aabb_list[i], aabb_list[j]))
				{
					//std::cout << "Colliision" << std::endl;
				}
			}
		}
		aabb_list.clear();
	}
	*/
	

	/*
	for (auto& a : aabb_list)
	{
		for (auto& b : aabb_list)
		{
			if(a == b) continue;
			aabb_intersect(a, b);
		}
	}
	*/
}



AABB AABBSystem::make_from_position_size(int x, int y, int w, int h)
{
	AABB box;
	box.x_min = x - w;
	box.y_min = y - h;
	box.x_max = x + w;
	box.y_max = y + h;

	return box;
}

bool AABBSystem::aabb_intersect(const AABB& a, const AABB& b)
{
	return (a.x_max > b.x_min &&
			b.x_max > a.x_min &&
			a.y_max > b.y_min &&
			b.y_max > a.y_min);
}