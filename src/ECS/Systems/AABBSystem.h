#pragma once


#include <vector>
#include "../System.h"

#include "../Components/AABB.h"
#include "../Components/Transform.h"
#include "../Components/Collision.h"

namespace ECS
{
	struct AABBSystem : System
	{
		AABBSystem();

		void start() override;
		void update() override;
		void render() override;
		void destroy() override;


	private:
		AABB make_from_position_size(int x, int y, int w, int h);
		bool aabb_intersect(const AABB& a, const AABB& b);
		std::vector<AABB> aabb_list;
	};
}
