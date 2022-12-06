#pragma once

#include "AABBSystem.h"

#include <chrono>

#include "../ECS.h"
#include "../Components/Transform.h"
#include "../../Common.h"
#include "../Components/Sprite.h"

void AABBSystem::init()
{
	// Create grid
	spatial_cells = make_grid(4);
}

void AABBSystem::update()
{
	if (entities.empty()) return;

	
	auto& manager = ECS::ECSManager::get_instance();

	//auto start = std::chrono::high_resolution_clock::now();

	// Set collision bit
	for (auto& entity : entities)
	{
		const Transform& transform = manager.get_component<Transform>(entity);
		Collision& collider = manager.get_component<Collision>(entity);

		// Create box for entity
		const int width = transform.scale * DEFAULT_SPRITE_W;
		const int height = transform.scale * DEFAULT_SPRITE_H;
		AABB box = make_from_position_size(transform.position.x, transform.position.y, width, height);

		
		// Clear bits dedicated for grid
		collider.mask &= 0xFFFF000;
		// Check for overlapping cells
		size_t index = 0;
		for (auto& cell : spatial_cells)
		{
			if (aabb_intersect(box, cell))
			{
				// Set collision bits with overlapping cell index
				collider.mask |= (1ULL << index);
				//std::cout << "setting cell bit" << std::endl;
			}
			index++;
		}
	}
	

	//auto stop = std::chrono::high_resolution_clock::now();
	//auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	//std::cout << "Setting bit masks duration: " << duration.count() << std::endl;


	int checks = 0;
	int collisions = 0;
	// Check collisions
	for (auto& a : entities)
	{
		auto const& mask_a = manager.get_component<Collision>(a).mask;
		for (auto& b : entities)
		{
			// Skip self
			if (a == b)
				continue;

			auto const& mask_b = manager.get_component<Collision>(b).mask;

			if ((mask_a & mask_b) != mask_a) 
				continue;

			

			AABB box_a;
			AABB box_b;

			{
				auto const& t = manager.get_component<Transform>(a);
				int width = DEFAULT_SPRITE_W * t.scale;
				int height = DEFAULT_SPRITE_H * t.scale;
				box_a = make_from_position_size(t.position.x, t.position.y, width, height);
			}
			{
				auto const& t = manager.get_component<Transform>(b);
				int width = DEFAULT_SPRITE_W * t.scale;
				int height = DEFAULT_SPRITE_H * t.scale;
				box_b = make_from_position_size(t.position.x, t.position.y, width, height);
			}

			//if (&box_a == &box_b)

			if (aabb_intersect(box_a, box_b))
			{
				// collision
				manager.get_component<Sprite>(a).color = { 255, 0, 0, 255 };
				collisions++;
			}
			else
			{
				manager.get_component<Sprite>(a).color = { 255, 255, 0, 255 };
			}
			checks++;
		}
	}

	//std::cout << "Collision checks: " << checks << std::endl;
	//std::cout << "Collisions: " << collisions << std::endl;

	/*
	// debug spatial
	for (auto& cell : spatial_cells)
	{
		SDL_Rect rect;
		rect.x = cell.x_min;
		rect.y = cell.y_min;
		rect.w = cell.x_max;
		rect.h = cell.y_max;
		SDL_SetRenderDrawColor(RENDERER, 255, 255, 255, 255);
		SDL_RenderDrawRect(RENDERER, &rect);
	}
	SDL_RenderPresent(RENDERER);
	*/
}



AABB AABBSystem::make_from_position_size(float x, float y, float w, float h)
{
	AABB box;
	box.y_min = y - h * 0.5;
	box.x_min = x - w * 0.5;
	box.x_max = x + w * 0.5;
	box.y_max = y + h * 0.5;

	return box;
}

bool AABBSystem::aabb_intersect(const AABB& a, const AABB& b)
{
	return (a.x_max > b.x_min &&
			b.x_max > a.x_min &&
			a.y_max > b.y_min &&
			b.y_max > a.y_min);
}

std::vector<AABB> AABBSystem::make_grid(const int size)
{
	std::vector<AABB> cells;
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			AABB box;
			int w = SCREEN_WIDTH / size;
			int h = SCREEN_HEIGHT / size;
			int x = w * j;
			int y = h * i;

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
