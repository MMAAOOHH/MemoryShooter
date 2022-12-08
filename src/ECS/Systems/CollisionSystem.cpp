#pragma once

#include "CollisionSystem.h"

#include <chrono>

#include "../ECS.h"
#include "../Components/Transform.h"
#include "../../Common.h"
#include "../Components/Sprite.h"
#include "../Types.h"
#include "../../Math.h"


void CollisionSystem::init()
{
	// Set system signature
	auto& manager = ECS::ECSManager::get_instance();
	ECS::Signature signature;
	signature.set(manager.get_component_type<Transform>(), true);
	signature.set(manager.get_component_type<Sprite>(), true);


	// Create spatial grid
	int size = 4;
	int index = 0;
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			SpatialCell cell;
			float width = SCREEN_WIDTH / size;
			float height = SCREEN_WIDTH / size;

			float x = width * i;
			float y = height * j;

			Vec2 center;
			center.x = width * 0.5 + x;
			center.y = height * 0.5 + y;

			cell.center = { center };
			cell.width = width;
			cell.height = height;

			spatial_grid[index] = cell;

			// used in old_update
			AABB box = make_from_position_size_centered(center.x, center.y, width, height);
			aabb_list.push_back(box);
			index++;
		}
	}
}
void CollisionSystem::update()
{
	if (entities.empty()) return;

	auto& manager = ECS::ECSManager::get_instance();


	// Clear previous
	transform_list.clear();
	collider_list.clear();
	did_collide_set.clear();
	for (auto& list : cell_id_lists)
	{
		list.clear();
	}


	// Get components
	for (const auto& entity : entities)
	{
		auto id = entity;
		const auto& transform = manager.get_component<Transform>(id);

		auto& collider = manager.get_component<Collider>(id);
		collider.collision = false;

		transform_list.insert({ id, transform });
		collider_list.insert({ id, collider });
	}
	// -----------
	// Broad phase
	// -----------
	// Assign to grid index
	for (auto& pair : transform_list)
	{
		int index = 0;
		for (const auto& cell : spatial_grid)
		{
			auto t = pair.second;
			float a_width = t.scale * DEFAULT_SPRITE_W;
			float a_height = t.scale * DEFAULT_SPRITE_H;

			AABB a = make_from_position_size_centered(t.position.x, t.position.y, a_width, a_height);
			AABB b = make_from_position_size_centered(cell.center.x, cell.center.y, cell.width, cell.height);

			// Check transform collision against
			if (aabb_intersect(a, b))
			{
				// Add entity ID to grid cell index
				cell_id_lists[index].push_back(pair.first);
			}
			index++;
		}
	}
	// -----------
	// Narrow phase
	// -----------
	int checks = 0;
	int collisions = 0;
	// Each grid cell
	for (auto const& list : cell_id_lists)
	{
		// Each entity checking against each other entity on the list
		for (auto& a : list)
		{
			for (auto& b : list)
			{
				int id_a = a;
				int id_b = b;
				// Skip self
				if (id_a == id_b) continue;

				auto& t_a = transform_list.at(id_a);
				auto& t_b = transform_list.at(id_b);

				float a_width = DEFAULT_SPRITE_W * t_a.scale;
				float a_height = DEFAULT_SPRITE_H * t_a.scale;

				float b_width = DEFAULT_SPRITE_W * t_b.scale;
				float b_height = DEFAULT_SPRITE_H * t_b.scale;

				AABB box_a = make_from_position_size_centered(t_a.position.x, t_a.position.y, a_width, a_height);
				AABB box_b = make_from_position_size_centered(t_b.position.x, t_b.position.y, b_width, b_height);

				if (aabb_intersect(box_a, box_b))
				{
					// collision
					auto& a_col = manager.get_component<Collider>(id_a);
					auto& b_col = manager.get_component<Collider>(id_b);

					a_col.collision = true;
					b_col.collision = true;

					a_col.from = b_col.tag;
					b_col.from = a_col.tag;


					collider_list.at(id_a).collision = true;
					collider_list.at(id_b).collision = true;
					collisions++;
				}
				checks++;
			}
		}
	}

}

	/*
	// Render spatial grid
	SDL_SetRenderDrawColor(RENDERER, 255, 255, 255, 255);
	for (auto& cell : spatial_cells)
	{
		SDL_Rect rect;
		rect.x = cell.x_min;
		rect.y = cell.y_min;
		rect.w = cell.x_max;
		rect.h = cell.y_max;
		
		SDL_RenderDrawRect(RENDERER, &rect);
	}
	//SDL_RenderPresent(RENDERER);
	*/


AABB CollisionSystem::make_from_position_size(float x, float y, float w, float h)
{
	AABB box;
	box.y_min = y - h;
	box.x_min = x - w;
	box.x_max = x + w;
	box.y_max = y + h;

	return box;
}

AABB CollisionSystem::make_from_position_size_centered(float x, float y, float w, float h)
{
	AABB box;
	box.y_min = y - h * 0.5;
	box.x_min = x - w * 0.5;
	box.x_max = x + w * 0.5;
	box.y_max = y + h * 0.5;

	return box;
}

bool CollisionSystem::aabb_intersect(const AABB& a, const AABB& b)
{
	return (a.x_max > b.x_min &&
			b.x_max > a.x_min &&
			a.y_max > b.y_min &&
			b.y_max > a.y_min);
}

std::vector<AABB> CollisionSystem::make_grid(const int size)
{
	std::vector<AABB> cells;
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			AABB box;
			int w = SCREEN_WIDTH / size;
			int h = SCREEN_HEIGHT / size;
			int x = w * i;
			int y = h * j;

			box.x_min = x;
			box.x_max = x + w;
			box.y_min = y;
			box.y_max = y + h;
			/*
			box.y_min = y - h * 0.5;
			box.x_min = x - w * 0.5;
			box.x_max = x + w * 0.5;
			box.y_max = y + h * 0.5;
			*/

			cells.push_back(box);
		}
	}
	return cells;
}
