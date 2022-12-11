#pragma once


#include <map>
#include <unordered_map>
#include <vector>
#include "../System.h"

#include "../Components/AABB.h"
#include "../Components/Collider.h"
#include "../Components/Transform.h"
#include "../../Math.h"

struct AABB
{
	float x_min;
	float y_min;
	float x_max;
	float y_max;
};

struct SpatialCell
{
	Vec2 center;
	float width = 0;
	float height = 0;
};

struct rect
{
	float x, y, w, h;
};

struct CollisionSystem : ECS::System
{
	CollisionSystem()
	{
		std::cout << "CollisionSystem created" << std::endl;
	}

	void init();
	void update();

private:
	
	// std::unordered_map<std::bitset<32>, std::vector<ECS::Entity>> do_broad_phase();
	// std::map<ECS::Entity, ECS::Entity> do_narrow_phase();

	AABB make_from_position_size(float x, float y, float w, float h);
	AABB make_from_position_size_centered(float x, float y, float w, float h);
	bool aabb_intersect(const AABB& a, const AABB& b);

	// New
	SpatialCell spatial_grid[16]{};
	std::vector<std::pair<Transform, Collider>>  cell_lists_array[16]{};
	std::vector<Transform> transform_list;
	std::unordered_map<ECS::Entity, Collider> collider_map;
	std::vector<std::pair<Transform, Collider>> data_list;

	std::vector<ECS::Entity> did_collide;

	// old
	std::vector<Transform> transform_list_old;
	std::vector<AABB> aabb_list;
	std::vector<AABB> spatial_cells;
	std::vector<AABB> make_grid(int size);
};
