#pragma once

#include "../Component.h"

struct Collider : ECS::Component
{
	enum Tag
	{
		player,
		enemy,
		player_projectile,
		enemy_projectile
	};
	Tag tag;
	Tag from;
	bool collision = false;
};
