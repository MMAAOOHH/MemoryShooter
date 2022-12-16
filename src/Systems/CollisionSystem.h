#pragma once

#include <unordered_map>
#include <vector>
#include "../ECS/System.h"

#include "../Components/Collider.h"
#include "../Components/Transform.h"
#include "../Math.h"

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

};
