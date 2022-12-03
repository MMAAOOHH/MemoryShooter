#pragma once


#include <vector>
#include "../System.h"

#include "../Components/AABB.h"
#include "../Components/Collision.h"


struct AABBSystem : ECS::System
{
	AABBSystem()
	{
		std::cout << "AABBSystem created" << std::endl;
	}

	// Todo: store managere reference
	void init();
	void update();

	private:
		AABB make_from_position_size(int x, int y, int w, int h);
		bool aabb_intersect(const AABB& a, const AABB& b);

		std::vector<AABB> aabb_list;
};
