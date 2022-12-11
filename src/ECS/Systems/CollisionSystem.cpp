#pragma once

#include "CollisionSystem.h"

#include <chrono>

#include "../ECS.h"
#include "../Components/Transform.h"
#include "../../Common.h"
#include "../Types.h"
#include "../../Math.h"

void CollisionSystem::init()
{
	// Set system signature
	auto& manager = ECS::ECSManager::get_instance();
	ECS::Signature signature;
	signature.set(manager.get_component_type<Transform>(), true);
	signature.set(manager.get_component_type<Collider>(), true);

	manager.set_system_signature<CollisionSystem>(signature);

	// Create spatial grid
	int size = 4;
	int index = 0;
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			SpatialCell cell;
			const float width = SCREEN_WIDTH / size;
			const float height = SCREEN_WIDTH / size;

			const float x = width * i;
			const float y = height * j;

			Vec2 center;
			center.x = width * 0.5 + x;
			center.y = height * 0.5 + y;

			cell.center = { center };
			cell.width = width;
			cell.height = height;

			spatial_grid[index] = cell;
			index++;
		}
	}
}

void CollisionSystem::update()
{
	if (entities.empty()) return;

	// Clear previous
	data_list.clear();
	for (auto& list : cell_lists_array)
		list.clear();

	auto& manager = ECS::ECSManager::get_instance();
	// Get components
	for (const auto& entity : entities)
	{
		auto& id = entity;
		auto& transform = manager.get_component<Transform>(id);
		auto& collider = manager.get_component<Collider>(id);

		data_list.emplace_back(std::pair<Transform, Collider>(transform, collider));
	}

	// Broad phase
	// -----------
	// Assign to grid index
	for (auto& pair : data_list)
	{
		int cell_index = 0;
		for (const auto& cell : spatial_grid)
		{
			const auto& t = pair.first;
			const float a_width = t.scale * DEFAULT_SPRITE_W;
			const float a_height = t.scale * DEFAULT_SPRITE_H;

			AABB a = make_from_position_size_centered(t.position.x, t.position.y, a_width, a_height);
			AABB b = make_from_position_size_centered(cell.center.x, cell.center.y, cell.width, cell.height);

			// Check transform collision against
			if (aabb_intersect(a, b))
			{
				// Adding entity to spatial cell list
				cell_lists_array[cell_index].push_back(pair);
			}
			cell_index++;
		}
	}

	// Narrow phase
	// -----------
	int checks = 0;
	int collisions = 0;
	// Each grid cell
	for (auto const& list : cell_lists_array)
	{
		// Each entity checking against each other entity on the list
		for (auto& a : list)
		{
			for (auto& b : list)
			{
				const auto id_a = a.first.entity_id;
				const auto id_b = b.first.entity_id;

				// Skip self id
				if (id_a == id_b) continue;

				const Tag& a_tag = a.second.tag;
				const Tag& b_tag = b.second.tag;

				// Skips checking for collisions for the same tag
				if (a_tag == b_tag) continue;

				// Collision check
				// ----------------
				const Transform& t_a = a.first;
				const Transform& t_b = b.first;

				const float a_width = DEFAULT_SPRITE_W * t_a.scale;
				const float a_height = DEFAULT_SPRITE_H * t_a.scale;

				const float b_width = DEFAULT_SPRITE_W * t_b.scale;
				const float b_height = DEFAULT_SPRITE_H * t_b.scale;

				AABB box_a = make_from_position_size_centered(t_a.position.x, t_a.position.y, a_width, a_height);
				AABB box_b = make_from_position_size_centered(t_b.position.x, t_b.position.y, b_width, b_height);

				if (aabb_intersect(box_a, box_b))
				{
					manager.add_component<Collision>(id_a, a_tag, b_tag);
					//manager.add_component<Collision>(id_b, b_tag, a_tag);
				}
			}
		}
	}
}


AABB CollisionSystem::make_from_position_size(float x, float y, float w, float h)
{
	AABB box;
	box.y_min = y - h;
	box.x_min = x - w;
	box.x_max = x + w;
	box.y_max = y + h;

	return box;
}

AABB CollisionSystem::make_from_position_size_centered(const float x, const float y, const float w, const float h)
{
	AABB box;
	box.y_min = y - h * 0.5f;
	box.x_min = x - w * 0.5f;
	box.x_max = x + w * 0.5f;
	box.y_max = y + h * 0.5f;


	return box;
}

bool CollisionSystem::aabb_intersect(const AABB& a, const AABB& b)
{
	return (a.x_max > b.x_min &&
			b.x_max > a.x_min &&
			a.y_max > b.y_min &&
			b.y_max > a.y_min);
}
