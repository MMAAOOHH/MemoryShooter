#pragma once


#include <vector>
#include "../System.h"

#include "../Components/AABB.h"
#include "../Components/Collision.h"
#include "../../Math.h"

struct AABB
{
	float x_min;
	float y_min;
	float x_max;
	float y_max;
};

struct rect
{
	float x, y, w, h;
};


struct AABBSystem : ECS::System
{
	AABBSystem()
	{
		std::cout << "AABBSystem created" << std::endl;
	}

	void init();
	void update();

private:
	AABB make_from_position_size(float x, float y, float w, float h);
	bool aabb_intersect(const AABB& a, const AABB& b);

	std::vector<AABB> make_grid(int size);
	//int map_to_cell(Vec2 v2);

	std::vector<AABB> spatial_cells;
	//std::vector<AABB> aabb_list;
};
