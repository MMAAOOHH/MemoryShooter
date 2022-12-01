#pragma once

#include "AABBSystem.h"
#include "../EntityManager.h"

ECS::AABBSystem::AABBSystem()
{
	add_component_signature<Transform>();
	add_component_signature<Collision>();

	std::cout << "AABB Sysem signature: ";
	for (auto const& s : signature)
	{
		std::cout << s << ' ';
	}
	std::cout << std::endl;
}

void ECS::AABBSystem::start()
{
}

void ECS::AABBSystem::update()
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

void ECS::AABBSystem::render()
{
}

void ECS::AABBSystem::destroy()
{
}

ECS::AABB ECS::AABBSystem::make_from_position_size(int x, int y, int w, int h)
{
	AABB box;
	box.x_min = x - w;
	box.y_min = y - h;
	box.x_max = x + w;
	box.y_max = y + h;

	return box;
}

bool ECS::AABBSystem::aabb_intersect(const ECS::AABB& a, const ECS::AABB& b)
{
	return (a.x_max > b.x_min &&
			b.x_max > a.x_min &&
			a.y_max > b.y_min &&
			b.y_max > a.y_min);
}