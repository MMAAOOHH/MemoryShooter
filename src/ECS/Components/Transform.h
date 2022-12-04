#pragma once

#include "../../Math.h"
#include "../Component.h"

struct Transform : ECS::Component
{
	Vec2 position;
	float rotation = 0.f;
	float scale = 1.f;

};
