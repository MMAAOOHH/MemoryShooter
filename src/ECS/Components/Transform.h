#pragma once

#include "../Component.h"

struct vec2
{
	int x = 0;
	int y = 0;
};


struct Transform : ECS::Component
{
	vec2 position;
	float rotation = 0.f;
	float scale = 1.f;

	void translate(vec2 v2)
	{}
};
