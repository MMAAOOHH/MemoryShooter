#pragma once


#include <map>
#include <unordered_map>
#include <vector>
#include "../System.h"

#include "../Components/AABB.h"
#include "../Components/Collision.h"
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
	Vec2 top_left;
	Vec2 top_right;
	Vec2 bot_left;
	Vec2 bot_right;

	Vec2 center;
	float width;
	float height;

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

	//int map_to_cell(Vec2 v2);

	std::vector<AABB> spatial_cells;

	std::vector<AABB> make_grid(int size);

	// New
	SpatialCell spatial_grid[16]{};
	std::vector<ECS::Entity> cell_id_lists[16]{};
	std::unordered_map<ECS::Entity, Transform> transform_list;
	std::unordered_map<ECS::Entity, Collision> collider_list;


	// old
	//std::vector<Transform> transform_list;
	std::vector<AABB> aabb_list;
};
