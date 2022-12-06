#pragma once

#include "../Component.h"

struct Collision : ECS::Component
{
	enum CollisionLayer
	{
		p = 17, // player
		e = 18 // enemy
	};

	Collision()
	{
		set_layer_mask(p, true);
		set_layer_mask(e, true);
	}

	std::bitset<32> mask;

	void set_layer_mask(const CollisionLayer layer, const bool b)
	{
		mask.set(layer, b);
	}
};
