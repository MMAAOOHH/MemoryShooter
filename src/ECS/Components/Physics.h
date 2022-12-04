#pragma once

#include "../Component.h"
#include "../../Math.h"

struct RigidBody : ECS::Component
{
	Vec2 velocity;
	Vec2 acceleration;

	float mass = 1.0f;
	bool use_gravity = true;

	void add_impulse(float force)
	{
		
	}
};