#pragma once


#include <vector>
#include "../System.h"

#include "../Components/AABB.h"
#include "../Components/Collision.h"


struct AABBSystem : ECS::System
{
	AABBSystem();

	void start() override;
	void update() override;
	void render() override;
	void destroy() override;

	private:
		AABB make_from_position_size(int x, int y, int w, int h);
		bool aabb_intersect(const AABB& a, const AABB& b);
		std::vector<AABB> aabb_list;};
