#pragma once

#include "AABBSystem.h"

#include "../ECS.h"
#include "../Components/Transform.h"

void AABBSystem::update()
{
	// make AABB box and store for each entry, ??kinda bad cause we already have our list??
	if (entities.empty()) return;

	// create AABB rects
	for (auto& entity : entities)
	{
		auto& transform = ECS::ECSManager::get_instance().get_component<Transform>(entity);
		AABB box = make_from_position_size(transform.position.x, transform.position.y, 16, 16);
		aabb_list.push_back(box);
	}

	if(aabb_list.empty()) return;

	// Check collision
	for (auto& a : aabb_list)
	{
		for (auto& b : aabb_list)
		{
			// Skip self
			if(&a == &b) continue;
			// Detect collision
			if (aabb_intersect(a, b))
			{
				//std::cout << "Colliision" << std::endl;
			}
		}
	}

	aabb_list.clear();
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