#pragma once

#include "../ECS/Component.h"
#include "../Math.h"

struct RigidBody : ECS::Component
{
	Vec2 velocity;
	Vec2 acceleration;
	float friction = 2.0f;
	float mass = 1.0f;
};