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
	//make_grid(size);
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
			index++;
		}
	}
}

void CollisionSystem::update()
{
	if (entities.empty()) return;

	auto& manager = ECS::ECSManager::get_instance();

	//std::unordered_map<std::bitset<32>, std::vector<ECS::Entity>> c_masks_temp_map; // don't allocate memory each frame

	transform_list.clear();
	collider_list.clear();
	for (auto& list : cell_id_lists)
	{
		list.clear();
	}

	// Get components
	for (const auto& entity : entities)
	{
		int id = entity;
		const auto& transform = manager.get_component<Transform>(id);
		const auto& collider = manager.get_component<Collision>(id);
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
					collisions++;
				}
				checks++;
			}
		}
	}
	//std::cout << "Possible collisions: " << checks << std::endl;
	/*
	// Render spatial grid
	SDL_SetRenderDrawColor(RENDERER, 255, 255, 255, 255);
	for (auto& cell : spatial_grid)
	{
		SDL_Rect rect;
		rect.x = cell.center.x - cell.width * 0.5;
		rect.y = cell.center.y - cell.height * 0.5;
		rect.w = cell.width;
		rect.h = cell.height;

		SDL_RenderDrawRect(RENDERER, &rect);
		SDL_RenderPresent(RENDERER);
	}
	//SDL_RenderPresent(RENDERER);
	*/
}

/*
	//auto start = std::chrono::high_resolution_clock::now();
	// Set collision bit
	for (auto& entity : entities)
	{
		const Transform& transform = manager.get_component<Transform>(entity);
		auto& mask = manager.get_component<Collision>(entity).mask;

		// Create box for entity
		const int width = transform.scale * DEFAULT_SPRITE_W;
		const int height = transform.scale * DEFAULT_SPRITE_H;
		AABB box = make_from_position_size(transform.position.x, transform.position.y, width, height);

		// Clear bits dedicated for grid
		mask &= 0xFFFF000;
		// Check for overlapping cells
		size_t index = 0;
		for (auto& cell : spatial_cells)
		{
			if (aabb_intersect(box, cell))
			{
				// Set collision bits with overlapping cell index
				mask |= (1ULL << index);
				//std::cout << "setting cell bit" << std::endl;
			}
			index++;
		}

		c_masks_temp_map[mask].push_back(entity);
		transform_list.push_back(transform);
	}

	//auto stop = std::chrono::high_resolution_clock::now();
	//auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	//std::cout << "Broad phase duration: " << duration.count() << std::endl;

	// -----------
	// Narrow phase
	// -----------

	// Check AABB collisions
	int checks = 0;
	int collisions = 0;
	for (auto const& pair : c_masks_temp_map)
	{
		auto levels = pair.first.count();
		const auto& list = pair.second;

		for (const auto& a : list)
		{
			for (const auto& b : list)
			{
				AABB box_a;
				AABB box_b;

				{
					auto const& t = transform_list[a];
					int width = DEFAULT_SPRITE_W * t.scale;
					int height = DEFAULT_SPRITE_H * t.scale;
					box_a = make_from_position_size(t.position.x, t.position.y, width, height);
				}
				{
					auto const& t = transform_list[b];
					int width = DEFAULT_SPRITE_W * t.scale;
					int height = DEFAULT_SPRITE_H * t.scale;
					box_b = make_from_position_size(t.position.x, t.position.y, width, height);
				}

				//if (&box_a == &box_b)

				if (aabb_intersect(box_a, box_b))
				{
					// collision

					collisions++;
				}
				checks++;
			}
		}
	}
}
		
	*/

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
